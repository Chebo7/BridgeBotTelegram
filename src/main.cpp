#include <cstdint>
#include <format>
#include <print>
#include <string>
#include <tgbot/tgbot.h>
#include <unordered_map>

enum ClientState { Default, WaitingForText };

int main() {
  const char *TELEGRAM_BOT_TOKEN = getenv("TELEGRAM_BOT_TOKEN");

  if (TELEGRAM_BOT_TOKEN == nullptr) {
    std::println("The environment variable for the bot token is not set. Set "
                 "it using \"export TELEGRAM_BOT_TOKEN=\"Your token\"\"");
    return 1;
  }

  const char *ADMIN_CHAT_ID = getenv("ADMIN_CHAT_ID");

  if (ADMIN_CHAT_ID == nullptr) {
    std::println("The environment variable for the admin chat is not set. Set "
                 "it using \"export ADMIN_CHAT_ID=\"Your Telegram ID\"\"");
    return 1;
  }

  std::unordered_map<int64_t, ClientState> clients;

  TgBot::Bot bot(TELEGRAM_BOT_TOKEN);
  bot.getEvents().onCommand("start", [&bot,
                                      &clients](TgBot::Message::Ptr message) {
    bot.getApi().sendMessage(
        message->chat->id,
        "Hey, if you want to send me a private message, leave a short message "
        "here explaining what happened or why you're writing, and I'll see "
        "your request.Thanks, this is to prevent spam and bots :)");
    clients.insert_or_assign(message->chat->id, ClientState::WaitingForText);
  });

  bot.getEvents().onNonCommandMessage([&bot, &clients, ADMIN_CHAT_ID](
                                          TgBot::Message::Ptr message) {
    std::println("User wrote: {}", message->text);

    auto it = clients.find(message->chat->id);
    if (it == clients.end() || it->second == ClientState::Default) {
      bot.getApi().sendMessage(
          message->chat->id,
          "Hmmm... I haven't learned to understand this command :(");
      return;
    }
    bot.getApi().sendMessage(message->chat->id, "Your message has been sent.");

    it->second = ClientState::Default;

    std::string clientUsername = message.get()->chat->username;

    if (clientUsername.empty()) {

      std::string prepareMessage = std::format(
          "The user do not have username, id: {},  wrote to you: {}",
          message->chat->id, message->text);

      bot.getApi().sendMessage(ADMIN_CHAT_ID, prepareMessage);
    } else {
      std::string prepareMessage = std::format("The @{} wrote to you: {}",
                                               clientUsername, message->text);
      bot.getApi().sendMessage(ADMIN_CHAT_ID, prepareMessage);
    }
  });

  try {
    std::string botUsername = bot.getApi().getMe()->username;

    if (botUsername.empty()) {
      std::println("Bot username empty");
    } else {
      std::println("Bot username is: {}", botUsername);
    }

    TgBot::TgLongPoll longPoll(bot);
    while (true) {
      std::println("Long poll started");
      longPoll.start();
    }
  } catch (TgBot::TgException &e) {
    std::println("Error: {}", e.what());
  }
  return 0;
}