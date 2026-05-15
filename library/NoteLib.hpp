#ifndef _LIB_HPP_
#define _LIB_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <limits>

// Заметка
class Note {
public:
    Note(const std::string& desc, int priority);
    std::string getDescription() const;
    int getPriority() const;
    bool isDone() const;
    void setDone(bool done);
private:
    std::string description;
    int priority;
    bool done;
};

// Блокнот
class Notebook {
public:
    void addNote(const std::string& desc, int priority);
    void listNotes() const;
    bool markDone(int index);
    bool deleteNote(int index);
    int size() const;
    const Note& getNote(int index) const;
private:
    std::vector<Note> notes;
};

void runNotebookApp();

#endif //_LIB_HPP_