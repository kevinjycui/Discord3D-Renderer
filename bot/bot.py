from PIL import Image
from websocket import create_connection
import ssl

import discord
from discord.ext import commands, tasks

import os
import json
import time


FRAMES_PER_REQ = 3
req_time = 2000

direction_emojis = (
    '⬅️', '⬆️', '⬇️', '➡️'
)
zoom_emojis = (
    '⏫', '⏬'
)

def convertGIF(pixels, output='sample.gif'):
    # frames = list(map(Image.open, files))
    frames = []
    for pixel in pixels:
        # print(pixel)
        frames.append(Image.frombuffer("RGB", (1200, 800), pixel))

    frames[0].save(output, format='GIF',
        append_images=frames[1:] + [frames[-1]]*20,
        save_all=True,
        duration=req_time//FRAMES_PER_REQ, loop=0)

client = create_connection("ws://localhost:9002", sslopt={"cert_reqs": ssl.CERT_NONE})
message = None

movement = None
angle = None
zoom = None

movement_control = None
angle_control = None
zoom_control = None

bot = commands.Bot(
    command_prefix='.',
    description='3D Render for Discord'
)

token = open('bot/credentials.txt').read().strip()

@bot.command()
async def render(ctx):
    global message, movement_control, angle_control, zoom_control, movement, angle, zoom
    if message is not None:
        await ctx.send('Error: There is already an instance being played elsewhere. Please quit before creating a new instance.')
        return

    movement = await ctx.send('Movement control')
    angle = await ctx.send('Angle control')
    zoom = await ctx.send('Zoom control')
    
    movement_control = movement.id
    angle_control = angle.id
    zoom_control = zoom.id

    for emoji in direction_emojis:
        await movement.add_reaction(emoji)
        await angle.add_reaction(emoji)
    for emoji in zoom_emojis:
        await zoom.add_reaction(emoji)

    message = await ctx.send("Loading...")

@bot.command()
async def quit(ctx):
    global message
    if message is None:
        await ctx.send('Error: There is no an instance being played.')
        return
    await message.delete()
    await movement.delete()
    await angle.delete()
    await zoom.delete()
    message = None
    await ctx.send('Successfully quit')

async def get_command_encode(message_id, emojis):
    code = 0
    control = await message.channel.fetch_message(message_id)

    for reaction in control.reactions:
        emoji_react = str(reaction.emoji)
        if emoji_react in emojis and reaction.count > 1:
            code += 2 ** emojis.index(emoji_react)
            
    return code

@tasks.loop(seconds=2)
async def render_loop():
    global message
    if message is not None:
        result = ''
        pixels = []
        start = time.time()
        while True:

            directions = {
                'movement': await get_command_encode(movement_control, direction_emojis),
                'angle': await get_command_encode(angle_control, direction_emojis),
                'zoom': await get_command_encode(zoom_control, zoom_emojis),
            }
            
            client.send(json.dumps(directions))
            recv = client.recv()
            if recv == b'0':
                break
            pixels.append(recv)
        convertGIF(pixels)

        req_time = time.time() - start

        old_message = message
        if message is not None:
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
