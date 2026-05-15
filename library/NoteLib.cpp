#include "NoteLib.hpp"

// Заметка
Note::Note(const std::string& desc, int prio)
    : description(desc), priority(prio), done(false) {
}

std::string Note::getDescription() const { return description; }
int Note::getPriority() const { return priority; }
bool Note::isDone() const { return done; }
void Note::setDone(bool d) { done = d; }

// Блокнот
void Notebook::addNote(const std::string& desc, int priority) {
    notes.push_back(Note(desc, priority));
}

void Notebook::listNotes() const {
    if (notes.empty()) {
        std::cout << "Нет заметок.\n";
        return;
    }
    for (size_t i = 0; i < notes.size(); ++i) {
        const Note& n = notes[i];
        std::cout << i + 1 << ". ";
        if (n.isDone()) std::cout << "[X] ";
        else std::cout << "[ ] ";
        std::cout << n.getDescription() << " (приоритет: " << n.getPriority() << ")\n";
    }
}

bool Notebook::markDone(int index) {
    if (index < 1 || index > static_cast<int>(notes.size())) return false;
    notes[index - 1].setDone(true);
    return true;
}

bool Notebook::deleteNote(int index) {
    if (index < 1 || index > static_cast<int>(notes.size())) return false;
    notes.erase(notes.begin() + index - 1);
    return true;
}

int Notebook::size() const { return notes.size(); }

const Note& Notebook::getNote(int index) const {
    return notes[index];
}

static std::string inputString(std::istream& in, std::ostream& out, const std::string& prompt) {
    std::string s;
    while (true) {
        out << prompt;
        std::getline(in, s);
        if (!s.empty()) break;
        out << "Ошибка: строка не может быть пустой. Повторите.\n";
    }
    return s;
}

static int inputPriority(std::istream& in, std::ostream& out, const std::string& prompt) {
    int p;
    while (true) {
        out << prompt;
        if (!(in >> p) || p < 1 || p > 3) {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            out << "Ошибка: введите число от 1 до 3.\n";
        }
        else {
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return p;
        }
    }
}

static int inputMenuChoice(std::istream& in, std::ostream& out, int min, int max) {
    int choice;
    while (true) {
        out << "Выберите пункт: ";
        if (!(in >> choice) || choice < min || choice > max) {
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            out << "Ошибка: введите число от " << min << " до " << max << ".\n";
        }
        else {
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}

// Запуск приложения
void runNotebookApp() {
    Notebook nb;
    while (true) {
        std::cout << "\n=== МЕНЮ ЗАМЕТОК ===\n";
        std::cout << "1. Добавить заметку\n";
        std::cout << "2. Показать все заметки\n";
        std::cout << "3. Отметить выполненной\n";
        std::cout << "4. Удалить заметку\n";
        std::cout << "5. Выход\n";
        int choice = inputMenuChoice(std::cin, std::cout, 1, 5);

        if (choice == 1) {
            std::string desc = inputString(std::cin, std::cout, "Описание: ");
            int prio = inputPriority(std::cin, std::cout, "Приоритет (1-высокий, 3-низкий): ");
            nb.addNote(desc, prio);
            std::cout << "Заметка добавлена.\n";
        }
        else if (choice == 2) {
            nb.listNotes();
        }
        else if (choice == 3) {
            if (nb.size() == 0) {
                std::cout << "Нет заметок.\n";
                continue;
            }
            nb.listNotes();
            int idx = inputMenuChoice(std::cin, std::cout, 1, nb.size());
            if (nb.markDone(idx))
                std::cout << "Отмечено как выполненное.\n";
            else
                std::cout << "Ошибка.\n";
        }
        else if (choice == 4) {
            if (nb.size() == 0) {
                std::cout << "Нет заметок.\n";
                continue;
            }
            nb.listNotes();
            int idx = inputMenuChoice(std::cin, std::cout, 1, nb.size());
            if (nb.deleteNote(idx))
                std::cout << "Удалено.\n";
            else
                std::cout << "Ошибка.\n";
        }
        else if (choice == 5) {
            std::cout << "До свидания!\n";
            break;
        }
    }
}