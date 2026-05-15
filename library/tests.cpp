#include "NoteLib.hpp"
//#include <cassert>
#include <sstream>
#include <iostream>

int test_note() {
    Note n("Купить хлеб", 2);
    if (n.getDescription() != "Купить хлеб") {
        std::cerr << "Ошибка: getDescription не работает" << std::endl;
        return 1;
    }
    if (n.getPriority() != 2) {
        std::cerr << "Ошибка: getPriority не работает" << std::endl;
        return 1;
    }
    if (n.isDone()) {
        std::cerr << "Ошибка: isDone должна быть false" << std::endl;
        return 1;
    }
    n.setDone(true);
    if (!n.isDone()) {
        std::cerr << "Ошибка: setDone не установил true" << std::endl;
        return 1;
    }
    return 0;
}

int test_notebook_add_and_list() {
    Notebook nb;
    nb.addNote("Заметка1", 1);
    nb.addNote("Заметка2", 3);
    if (nb.size() != 2) {
        std::cerr << "Ошибка: неправильный размер после добавления 2 заметок" << std::endl;
        return 1;
    }
    if (nb.getNote(0).getDescription() != "Заметка1") {
        std::cerr << "Ошибка: первая заметка не 'Заметка1'" << std::endl;
        return 1;
    }
    if (nb.getNote(1).getPriority() != 3) {
        std::cerr << "Ошибка: приоритет второй заметки не 3" << std::endl;
        return 1;
    }
    return 0;
}

int test_notebook_mark_done() {
    Notebook nb;
    nb.addNote("Тест", 2);
    if (!nb.markDone(1)) {
        std::cerr << "Ошибка: markDone для индекса 1 не вернул true" << std::endl;
        return 1;
    }
    if (!nb.getNote(0).isDone()) {
        std::cerr << "Ошибка: заметка не помечена как выполненная" << std::endl;
        return 1;
    }
    if (nb.markDone(5)) {
        std::cerr << "Ошибка: markDone для неверного индекса вернул true" << std::endl;
        return 1;
    }
    return 0;
}

int test_notebook_delete() {
    Notebook nb;
    nb.addNote("A", 1);
    nb.addNote("B", 2);
    if (!nb.deleteNote(1)) {
        std::cerr << "Ошибка: удаление заметки с индексом 1 не удалось" << std::endl;
        return 1;
    }
    if (nb.size() != 1) {
        std::cerr << "Ошибка: размер после удаления не равен 1" << std::endl;
        return 1;
    }
    if (nb.getNote(0).getDescription() != "B") {
        std::cerr << "Ошибка: после удаления осталась не та заметка" << std::endl;
        return 1;
    }
    if (nb.deleteNote(10)) {
        std::cerr << "Ошибка: удаление с неверным индексом вернуло true" << std::endl;
        return 1;
    }
    return 0;
}

int test_notebook_empty_operations() {
    Notebook nb;
    nb.listNotes();
    if (nb.markDone(1)) {
        std::cerr << "Ошибка: markDone на пустом блокноте вернул true" << std::endl;
        return 1;
    }
    if (nb.deleteNote(1)) {
        std::cerr << "Ошибка: deleteNote на пустом блокноте вернул true" << std::endl;
        return 1;
    }
    return 0;
}

int main() {
    if (test_note() != 0) return 1;
    if (test_notebook_add_and_list() != 0) return 1;
    if (test_notebook_mark_done() != 0) return 1;
    if (test_notebook_delete() != 0) return 1;
    if (test_notebook_empty_operations() != 0) return 1;
    std::cout << "Все тесты пройдены." << std::endl;
    return 0;
}