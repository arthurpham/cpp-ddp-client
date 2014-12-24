#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

void on_message(client* webSocketClient, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << msg->get_payload() << std::endl;

    if (msg->get_payload() == "{\"msg\":\"ping\"}")
    {
    	std::string subMessage = "{ \"msg\": \"pong\" }";
     	webSocketClient->send(hdl, subMessage, msg->get_opcode());
    }
}

void on_open(client* webSocketClient, websocketpp::connection_hdl hdl)
{
    std::string connectMessage = "{ \"msg\": \"connect\", \"version\": \"1\", \"support\": [\"1\"] }";
    webSocketClient->send(hdl, connectMessage, websocketpp::frame::opcode::text);
}

int main(int argc, char* argv[]) {
	//std::string uri("ws://0.0.0.0:3000/websocket");
    std::string uri("ws://my_app_name.meteor.com/websocket");
	std::cout << "Connection to " << uri << std::endl;

	client ws_client;

	ws_client.init_asio();
    ws_client.set_open_handler(bind(&on_open,&ws_client,::_1));
    ws_client.set_message_handler(bind(&on_message,&ws_client,::_1,::_2));

    websocketpp::lib::error_code ec;
	client::connection_ptr con = ws_client.get_connection(uri, ec);

	ws_client.connect(con);
	ws_client.run();


}
