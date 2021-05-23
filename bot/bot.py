from PIL import Image
from websocket import create_connection
import ssl

import discord
from discord.ext import commands, tasks

import os
import json
import time


def convertGIF(pixels, output='sample.gif'):
    # frames = list(map(Image.open, files))
    frames = []
    for pixel in pixels:
        # print(pixel)
        frames.append(Image.frombuffer("RGB", (1200, 800), pixel))

    frames[0].save(output, format='GIF',
        append_images=frames[1:] + [frames[-1]]*20,
        save_all=True,
        duration=150, loop=0)

client = create_connection("ws://localhost:9002", sslopt={"cert_reqs": ssl.CERT_NONE})
message = None

bot = commands.Bot(
    command_prefix='.',
    description='3D Render for Discord'
)

token = open('bot/credentials.txt').read().strip()

@bot.command()
async def render(ctx):
    global message
    if message is not None:
        await ctx.send('Error: There is already an instance being played elsewhere. Please quit before creating a new instance.')
        return
    message = await ctx.send("Loading...")

@bot.command()
async def quit(ctx):
    global message
    if message is None:
        await ctx.send('Error: There is no an instance being played.')
        return
    await message.delete()
    message = None
    await ctx.send('Successfully quit')

@tasks.loop(seconds=2)
async def render_loop():
    global message
    if message is not None:
        result = ''
        pixels = []
        while True:
            client.send(json.dumps({"action": 0}))
            recv = client.recv()
            if recv == b'0':
                break
            pixels.append(recv)
        convertGIF(pixels)
        old_message = message
        message = await message.channel.send(file=discord.File('sample.gif'))
        await old_message.delete()

@render_loop.before_loop
async def render_loop_before():
    await bot.wait_until_ready()

@bot.event
async def on_ready():
    await bot.change_presence(
        activity=discord.Activity(
            type=discord.ActivityType.playing,
            name='Gex'
        )
    )
    print('Bot ready!')

if __name__ == '__main__':
    render_loop.start()
    bot.run(token)
