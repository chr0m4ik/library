#include "NoteLib.hpp"
#include <cassert>
#include <sstream>
#include <iostream>

#define ASSERT_MSG(condition, message) assert((condition) && (message))

int test_note() {
    Note n("Купить хлеб", 2);
    ASSERT_MSG(n.getDescription() == "Купить хлеб", "getDescription failed");
    ASSERT_MSG(n.getPriority() == 2, "getPriority failed");
    ASSERT_MSG(!n.isDone(), "isDone should be false");
    n.setDone(true);
    ASSERT_MSG(n.isDone(), "setDone failed");
    return 0;
}

// Тест на добавление и отображение заметок
int test_notebook_add_and_list() {
    Notebook nb;
    nb.addNote("Заметка1", 1);
    nb.addNote("Заметка2", 3);
    ASSERT_MSG(nb.size() == 2, "size should be 2");
    ASSERT_MSG(nb.getNote(0).getDescription() == "Заметка1", "first note wrong");
    ASSERT_MSG(nb.getNote(1).getPriority() == 3, "priority should be 3");
    return 0;
}

// Тест на отметку заметки как выполненной
int test_notebook_mark_done() {
    Notebook nb;
    nb.addNote("Тест", 2);
    ASSERT_MSG(nb.markDone(1), "markDone(1) should return true");
    ASSERT_MSG(nb.getNote(0).isDone(), "note should be marked done");
    ASSERT_MSG(!nb.markDone(5), "markDone(5) should return false");
    return 0;
}

// Тест на удаление заметки
int test_notebook_delete() {
    Notebook nb;
    nb.addNote("A", 1);
    nb.addNote("B", 2);
    ASSERT_MSG(nb.deleteNote(1), "deleteNote(1) should return true");
    ASSERT_MSG(nb.size() == 1, "size should be 1 after delete");
    ASSERT_MSG(nb.getNote(0).getDescription() == "B", "wrong note after delete");
    ASSERT_MSG(!nb.deleteNote(10), "deleteNote(10) should return false");
    return 0;
}

// Тест на операции с пустым блокнотом
int test_notebook_empty_operations() {
    Notebook nb;
    nb.listNotes();
    ASSERT_MSG(!nb.markDone(1), "markDone on empty should return false");
    ASSERT_MSG(!nb.deleteNote(1), "deleteNote on empty should return false");
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