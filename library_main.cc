#include "header/library.h"

int main()
{
    Library lib;
    while(true)
    {
        string command, title;
        cin >> command;
        if(command == "add_book")
        {
            Book book;
            cin >> book;
            lib.AddBook(book.title(), book.total());
        }
        else if(command == "add_magazine")
        {
            Magazine magazine;
            cin >> magazine;
            lib.AddMagazine(magazine.Book::title(), magazine.total(), magazine.year(), magazine.month());
        }
        else if(command == "print")
        {
            lib.PrintAll();
        }
        else if(command == "delete")
        {
            cin >> title;
            lib.DeleteBook(title);
        }
        else if(command == "lend")
        {
            cin >> title;
            lib.Lend(title);
        }
        else if(command == "return")
        {
            cin >> title;
            lib.Return(title);
        }
        else    break;
    }
    return 0;
}
