#include <iostream>
#include <bits/stdc++.h>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "../protoFiles/chatBot.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using chatBot::chat;
using chatBot::chatBotReply;
using chatBot::chatBotRequest;

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
	  : stub_(chat::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SayHello(const std::string& user) {
	// Data we are sending to the server.
	chatBotRequest request;
	request.set_name(user);

	// Container for the data we expect from the server.
	chatBotReply reply;

	// Context for the client. It could be used to convey extra information to
	// the server and/or tweak certain RPC behaviors.
	ClientContext context;

	// The actual RPC.
	Status status = stub_->SayHello(&context, request, &reply);

	// Act upon its status.
	if (status.ok()) {
		return reply.message();
	  } else {
		std::cout << status.error_code() << ": " << status.error_message()
				  << std::endl;
		return "RPC failed";
	  }
  }
  std::string SayHelloAgain(const std::string& user)
  {
	// Follows the same pattern as SayHello.
	chatBotRequest request;
	request.set_name (user);
	chatBotReply reply;
	ClientContext context;

	// Here we can use the stub's newly available method we just added.
	Status status = stub_->SayHelloAgain (&context, request, &reply);
	if (status.ok ())
	  {
		return reply.message ();
	  }
	else
	  {
		std::cout << status.error_code () << ": " << status.error_message ()
				  << std::endl;
		return "RPC failed";
	  }
  }

 private:
  std::unique_ptr<chat::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint specified by
  // the argument "--target=" which is the only expected argument.
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).
  std::string target_str;
  std::string arg_str("--target");
  if (argc > 1) {
	  std::string arg_val = argv[1];
	  size_t start_pos = arg_val.find(arg_str);
	  if (start_pos != std::string::npos) {
		  start_pos += arg_str.size();
		  if (arg_val[start_pos] == '=') {
			  target_str = arg_val.substr(start_pos + 1);
			} else {
			  std::cout << "The only correct argument syntax is --target="
						<< std::endl;
			  return 0;
			}
		} else {
		  std::cout << "The only acceptable argument is --target=" << std::endl;
		  return 0;
		}
	} else {
	  target_str = "localhost:8080";
	}
  GreeterClient greeter(
	  grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  std::string user;

  for(;;){
	  std::getline (std::cin, user);

	  std::string reply = greeter.SayHello(user);
	  std::cout << "Greeter received: " << reply << std::endl;

	  reply = greeter.SayHelloAgain(user);
	  std::cout << "Greeter received: " << reply << std::endl;
	}

  return 0;
}