#include "tgbot/types/BotCommandScope.h"
#include "tgbot/types/BotCommandScopeChat.h"
#include "tgbot/types/Chat.h"
#include "tgbot/types/Message.h"
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <tgbot/tgbot.h>
#include <unordered_map>

enum ClientState { Default, WaitingForText };

int main() {
  const char *TOKEN = getenv("TELEGRAM_BOT_TOKEN");
  std::unordered_map<int64_t, ClientState> Clients;

  TgBot::Bot bot(TOKEN);
  bot.getEvents().onCommand("start", [&bot,
                                      &Clients](TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(
        message->chat->id,
        "Hey, if you want to send me a private message, leave a short message "
        "here explaining what happened or why you're writing, and I'll see "
        "your request.Thanks, this is to prevent spam and bots :)     ");
    Clients.emplace(message->chat->id, ClientState::WaitingForText);
  });

  bot.getEvents().onNonCommandMessage(
      [&bot, &Clients](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
          return;
        }

        if (Clients[message->chat->id] == 0) {
          bot.getApi().sendMessage(
              message->chat->id,
              "Hmmm... I haven't learned to understand this command :(");
        } else if (Clients[message->chat->id] == ClientState::WaitingForText) {
          bot.getApi().sendMessage(message->chat->id,
                                   "Your message has been sent.");
          Clients[message->chat->id] = ClientState::Default;

          std::string clientUsername = message.get()->chat->username;

          bot.getApi().sendMessage(7960664163,
                                   "The @" + clientUsername +
                                       " wrote to you: " + message->text);
        }
      });

  try {
    printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
    TgBot::TgLongPoll longPoll(bot);
    while (true) {
      printf("Long poll started\n");
      longPoll.start();
    }
  } catch (TgBot::TgException &e) {
    printf("error: %s\n", e.what());
  }
  return 0;
}