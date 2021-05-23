#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

#include <functional>
#include <stdio.h>
#include <string>
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "../include/main.h"
#include "../include/main_socket.h"

 
typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

 
void on_message(server* s, websocketpp::connection_hdl hdl, server::message_ptr msg)
{
    rapidjson::Document d;
    d.Parse(msg->get_payload().c_str());

    rapidjson::Value& action = d["action"];

    int rt = gl_Loop();

    if (rt == 1) {
        s->send(hdl, "0", websocketpp::frame::opcode::binary);
        return;
    }

    try {	
        // std::ostringstream ss;
        // ss << "frames/" << img_index << ".png";
        // std::string path = ss.str();

        // stbi_flip_vertically_on_write(true);
        // stbi_write_png(path.c_str(), WIDTH, HEIGHT, nrChannels, pixels, stride);

        s->send(hdl, pixels, sizeof(pixels), websocketpp::frame::opcode::binary);
    } catch (websocketpp::exception const & e) {
        std::cout << "Response failed: (" << e.what() << ")\n";
    }
}

void on_open(server* s, websocketpp::connection_hdl hdl)
{
    gl_Init();
}

void on_close(server* s, websocketpp::connection_hdl hdl)
{
    gl_Close();
    // s->stop_listening();   
}

class ws_server 
{
public:
    ws_server()
    {
        // m_endpoint.set_error_channels(websocketpp::log::elevel::all);
        // m_endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);

        m_endpoint.clear_access_channels(websocketpp::log::alevel::all);

        m_endpoint.set_message_handler(bind(&on_message, &m_endpoint, ::_1, ::_2));
        m_endpoint.set_open_handler(bind(&on_open, &m_endpoint, ::_1));
        m_endpoint.set_close_handler(bind(&on_close, &m_endpoint, ::_1));
 
        m_endpoint.init_asio();
    }
 
    void run()
    {
        m_endpoint.listen(9002);
        m_endpoint.start_accept();
        std::cout << "WebSocket Server Running on ws://localhost:9002/\n";
        m_endpoint.run();
    }

private:
    server m_endpoint;
};
 
int main() 
{
    ws_server s;

    s.run();
    return 0;
}
