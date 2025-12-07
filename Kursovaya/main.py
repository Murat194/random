import telebot
from telebot import types
import json
import os

bot = telebot.TeleBot('8516262739:AAFRFyMDF0-HkZDGB7oKgLIlM9TvtxHY_2g')

JOKES_FILE = 'jokes_database.json'
USERS_FILE = 'users_settings.json'

def load_jokes():
    if os.path.exists(JOKES_FILE):
        try:
            with open(JOKES_FILE, 'r', encoding='utf-8') as f:
                jokes_data = json.load(f)
                return jokes_data
        except Exception as e:
            print(f"Ошибка загрузки базы данных: {e}")
            return []
    else:
        print(f"Файл {JOKES_FILE} не найден. Создайте файл с базой данных.")
        return []

def load_user_settings():
    if os.path.exists(USERS_FILE):
        try:
            with open(USERS_FILE, 'r', encoding='utf-8') as f:
                return json.load(f)
        except:
            return {}
    return {}

def save_user_settings(settings):
    with open(USERS_FILE, 'w', encoding='utf-8') as f:
        json.dump(settings, f, ensure_ascii=False, indent=2)

def get_all_genres(jokes):
    genres = set()
    for joke in jokes:
        if 'genres' in joke:
            for genre in joke['genres']:
                genres.add(genre)
    return sorted(list(genres))

def get_random_joke(user_id, jokes, user_settings):
    adult_allowed = user_settings.get(str(user_id), {}).get('adult_allowed', False)
    
    filtered_jokes = jokes.copy()
    if not adult_allowed:
        filtered_jokes = [joke for joke in jokes if not joke.get('is_adult', False)]
    
    if not filtered_jokes:
        return None
    
    import random
    return random.choice(filtered_jokes)

def get_jokes_by_genre(genre, user_id, jokes, user_settings):
    adult_allowed = user_settings.get(str(user_id), {}).get('adult_allowed', False)
    
    filtered_jokes = []
    for joke in jokes:
        if 'genres' in joke and genre in joke['genres']:
            if adult_allowed or not joke.get('is_adult', False):
                filtered_jokes.append(joke)
    
    return filtered_jokes

@bot.message_handler(commands=['start'])
def main(message):
    markup = types.ReplyKeyboardMarkup(resize_keyboard=True)
    item1 = types.KeyboardButton("🎲 Случайный анекдот")
    item2 = types.KeyboardButton("📂 По жанру")
    item3 = types.KeyboardButton("⚙️ Настройки")
    markup.add(item1, item2, item3)
    
    bot.send_message(message.chat.id, 
                     'Привет!\nЭто бот для улучшения твоего дня! Здесь ты можешь почитать смешные и не очень анекдоты.\n\n'
                     'Используйте кнопки ниже для навигации:',
                     reply_markup=markup,
                     parse_mode='html')

@bot.message_handler(func=lambda message: message.text == "🎲 Случайный анекдот")
def send_random_joke(message):
    jokes = load_jokes()
    user_settings = load_user_settings()
    
    if not jokes:
        bot.send_message(message.chat.id, "База данных анекдотов пуста или не загружена.")
        return
    
    joke = get_random_joke(message.from_user.id, jokes, user_settings)
    
    if joke:
        genres_text = ""
        if 'genres' in joke and joke['genres']:
            genres_text = f"\n\n🏷️ Теги: {', '.join(joke['genres'])}"
        
        adult_text = " 🔞" if joke.get('is_adult', False) else ""
        
        bot.send_message(message.chat.id, f"{joke['text']}{genres_text}{adult_text}")
    else:
        bot.send_message(message.chat.id, "Нет доступных анекдотов с текущими настройками фильтра.")

@bot.message_handler(func=lambda message: message.text == "📂 По жанру")
def show_genres(message):
    jokes = load_jokes()
    
    if not jokes:
        bot.send_message(message.chat.id, "База данных анекдотов пуста или не загружена.")
        return
    
    genres = get_all_genres(jokes)
    
    if not genres:
        bot.send_message(message.chat.id, "В базе данных нет жанров.")
        return
    
    markup = types.InlineKeyboardMarkup()
    
    for i in range(0, len(genres), 2):
        row = []
        row.append(types.InlineKeyboardButton(genres[i], callback_data=f"genre_{genres[i]}"))
        if i + 1 < len(genres):
            row.append(types.InlineKeyboardButton(genres[i + 1], callback_data=f"genre_{genres[i + 1]}"))
        markup.add(*row)
    
    bot.send_message(message.chat.id, "Выберите жанр:", reply_markup=markup)

@bot.callback_query_handler(func=lambda call: call.data.startswith('genre_'))
def handle_genre_selection(call):
    genre = call.data.replace('genre_', '')
    jokes = load_jokes()
    user_settings = load_user_settings()
    
    genre_jokes = get_jokes_by_genre(genre, call.from_user.id, jokes, user_settings)
    
    if not genre_jokes:
        bot.answer_callback_query(call.id, f"Нет анекдотов в жанре '{genre}' с текущими настройками.")
        return
    
    import random
    joke = random.choice(genre_jokes)
    
    genres_text = ""
    if 'genres' in joke and joke['genres']:
        genres_text = f"\n\n🏷️ Теги: {', '.join(joke['genres'])}"
    
    adult_text = " 🔞" if joke.get('is_adult', False) else ""
    
    bot.edit_message_text(chat_id=call.message.chat.id,
                          message_id=call.message.message_id,
                          text=f"Жанр: {genre}\n\n{joke['text']}{genres_text}{adult_text}")

@bot.message_handler(func=lambda message: message.text == "⚙️ Настройки")
def show_settings(message):
    user_settings = load_user_settings()
    user_id = str(message.from_user.id)
    
    adult_allowed = user_settings.get(user_id, {}).get('adult_allowed', False)
    
    markup = types.InlineKeyboardMarkup()
    
    adult_text = "✅ 18+ включено" if adult_allowed else "❌ 18+ выключено"
    markup.add(types.InlineKeyboardButton(adult_text, callback_data="toggle_adult"))
    
    jokes = load_jokes()
    jokes_count = len(jokes) if jokes else 0
    adult_count = len([j for j in jokes if j.get('is_adult', False)]) if jokes else 0
    markup.add(types.InlineKeyboardButton(f"📊 Инфо о базе ({jokes_count} анекдотов, {adult_count} 18+)", callback_data="db_info"))
    
    bot.send_message(message.chat.id, 
                     "⚙️ Настройки бота:\n\n"
                     f"• Режим 18+: {'Включен' if adult_allowed else 'Выключен'}\n"
                     f"• Анекдотов в базе: {jokes_count}\n"
                     f"• Из них 18+: {adult_count}",
                     reply_markup=markup)

@bot.callback_query_handler(func=lambda call: call.data in ['toggle_adult', 'db_info'])
def handle_settings_buttons(call):
    if call.data == 'toggle_adult':
        user_settings = load_user_settings()
        user_id = str(call.from_user.id)
        
        if user_id not in user_settings:
            user_settings[user_id] = {}
        
        current = user_settings[user_id].get('adult_allowed', False)
        user_settings[user_id]['adult_allowed'] = not current
        
        save_user_settings(user_settings)
        
        adult_allowed = user_settings[user_id]['adult_allowed']
        
        markup = types.InlineKeyboardMarkup()
        adult_text = "✅ 18+ включено" if adult_allowed else "❌ 18+ выключено"
        markup.add(types.InlineKeyboardButton(adult_text, callback_data="toggle_adult"))
        
        jokes = load_jokes()
        jokes_count = len(jokes) if jokes else 0
        adult_count = len([j for j in jokes if j.get('is_adult', False)]) if jokes else 0
        markup.add(types.InlineKeyboardButton(f"📊 Инфо о базе ({jokes_count} анекдотов, {adult_count} 18+)", callback_data="db_info"))
        
        bot.edit_message_text(chat_id=call.message.chat.id,
                              message_id=call.message.message_id,
                              text=f"⚙️ Настройки бота:\n\n"
                                   f"• Режим 18+: {'Включен' if adult_allowed else 'Выключен'}\n"
                                   f"• Анекдотов в базе: {jokes_count}\n"
                                   f"• Из них 18+: {adult_count}",
                              reply_markup=markup)
        
        status = "включен" if adult_allowed else "выключен"
        bot.answer_callback_query(call.id, f"Режим 18+ {status}")
    
    elif call.data == 'db_info':
        jokes = load_jokes()
        jokes_count = len(jokes) if jokes else 0
        adult_count = len([j for j in jokes if j.get('is_adult', False)]) if jokes else 0
        
        genres_count = {}
        for joke in jokes:
            if 'genres' in joke:
                for genre in joke['genres']:
                    genres_count[genre] = genres_count.get(genre, 0) + 1
        
        genres_info = "\n".join([f"• {genre}: {count}" for genre, count in sorted(genres_count.items())])
        
        bot.answer_callback_query(
            call.id,
            f"База данных: {jokes_count} анекдотов\n18+: {adult_count}\n\nЖанры:\n{genres_info}",
            show_alert=True
        )

@bot.message_handler(func=lambda message: True)
def handle_other_messages(message):
    if message.text == "/help":
        help_text = (
            "📖 Помощь по боту:\n\n"
            "🎲 Случайный анекдот - получить случайный анекдот\n"
            "📂 По жанру - выбрать анекдот по жанру\n"
            "⚙️ Настройки - настройки фильтра 18+\n\n"
            "Команды:\n"
            "/start - начать работу с ботом\n"
            "/help - показать эту справку\n"
            "/stats - статистика базы данных"
        )
        bot.send_message(message.chat.id, help_text)
    
    elif message.text == "/stats":
        jokes = load_jokes()
        jokes_count = len(jokes) if jokes else 0
        adult_count = len([j for j in jokes if j.get('is_adult', False)]) if jokes else 0
        
        genres_count = {}
        for joke in jokes:
            if 'genres' in joke:
                for genre in joke['genres']:
                    genres_count[genre] = genres_count.get(genre, 0) + 1
        
        stats_text = (
            f"📊 Статистика базы данных:\n\n"
            f"• Всего анекдотов: {jokes_count}\n"
            f"• Анекдотов 18+: {adult_count}\n"
            f"• Анекдотов без 18+: {jokes_count - adult_count}\n"
            f"• Жанров: {len(genres_count)}\n\n"
            f"Топ-5 жанров:\n"
        )
        
        sorted_genres = sorted(genres_count.items(), key=lambda x: x[1], reverse=True)[:5]
        for i, (genre, count) in enumerate(sorted_genres, 1):
            stats_text += f"{i}. {genre}: {count}\n"
        
        bot.send_message(message.chat.id, stats_text)
    
    else:
        bot.send_message(message.chat.id, "Используйте кнопки меню или команды:\n/start - главное меню\n/help - помощь")

if __name__ == "__main__":
    print("Бот запущен...")
    bot.polling(non_stop=True)
