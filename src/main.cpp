#include <iostream>
#include <string>
#include <tgbot/tgbot.h>
#include <unordered_map>

enum ClientState { Default, WaitingForText };

int main() {
  const char *TOKEN = getenv("TELEGRAM_BOT_TOKEN");
  const int64_t ADMIN_CHAT_ID{};

  std::unordered_map<int64_t, ClientState> Clients;

  TgBot::Bot bot(TOKEN);
  bot.getEvents().onCommand("start", [&bot,
                                      &Clients](TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(
        message->chat->id,
        "Hey, if you want to send me a private message, leave a short message "
        "here explaining what happened or why you're writing, and I'll see "
        "your request.Thanks, this is to prevent spam and bots :)     ");
    Clients.insert_or_assign(message->chat->id, ClientState::WaitingForText);
  });

  bot.getEvents().onNonCommandMessage(
      [&bot, &Clients, ADMIN_CHAT_ID](TgBot::Message::Ptr message) {
        std::cout << "User wrote " + message->text << std::endl;

        if (!Clients.contains(message->chat->id)) {
          bot.getApi().sendMessage(
              message->chat->id,
              "Hmmm... I haven't learned to understand this command :(");
        } else if (Clients[message->chat->id] == ClientState::WaitingForText) {
          bot.getApi().sendMessage(message->chat->id,
                                   "Your message has been sent.");
          Clients.insert_or_assign(message->chat->id, ClientState::Default);

          std::string clientUsername = message.get()->chat->username;

          bot.getApi().sendMessage(ADMIN_CHAT_ID,
                                   "The @" + clientUsername +
                                       " wrote to you: " + message->text);
        }
      });

  try {
    std::cout << "Bot username: " + bot.getApi().getMe()->username << std::endl;
    TgBot::TgLongPoll longPoll(bot);
    while (true) {
      std::cout << "Long poll started" << std::endl;
      longPoll.start();
    }
  } catch (TgBot::TgException &e) {
    std::cout << "Error: " << e.what();
  }
  return 0;
}