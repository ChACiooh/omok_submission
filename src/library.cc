#include "../header/library.h"
#include <utility>
#include <cstdio>

/*** Book definition ***/
Book::Book(const Book& book)
{
    //cout << "Book(const Book& book)" << endl;
    title_ = book.title();
    total_ = book.total();
    stock_ = book.stock();
}

Book::Book(string title, int total)
{
    //cout << "Book(string title, int total)" << endl;
    title_ = title;
    total_ = total;
    stock_ = total_;
}

void Book::addtotal(int num)
{
    total_ += num;
    addstock(num);
}

void Book::addstock(int num)
{
    stock_ += num;
}

bool Book::Lend(int count = 1)
{
    bool res = (stock_ - count >= 0);
    if(res) addstock(-count);
    return res;
}

bool Book::Return(int count = 1)
{
    bool res = (stock_ + count <= total_);
    if(res) addstock(count);
    return res;
}

/*** Magazine definition ***/
Magazine::Magazine(const Magazine& magazine)
{
    //cout << "Magazine(const Magazine& magazine)" << endl;
    SetTitle(magazine.Book::title());
    SetTotal(magazine.total());
    SetStock(magazine.stock());
    year_ = magazine.year();
    month_ = magazine.month();
}

Magazine::Magazine(string title, int total, int year, int month):Book(title, total)
{
    /*SetTitle(title);
    SetTotal(total);
    SetStock(total);*/
    //cout << "Magazine(string title, int total, int year, int month)" << endl;
    year_ = year;
    month_ = month;
}

string itoa(int num)
{
    bool flag = num < 0;
    if(flag) num = -num;
    string res = "";
    while(num>0)
    {
        char r = num%10+'0';
        res = r + res;
        num /= 10;
    }
    return res;
}

string Magazine::title() const
{
    string res = Book::title()+"("+itoa(year_)+"/"+itoa(month_)+")";
    return res;
}

/*** istream overloading ***/
istream& operator>>(istream& is, Book& book)
{
    string title;
    int total;
    is >> title >> total;
    book.SetTitle(title);
    book.addtotal(total);
    return is;
}

istream& operator>>(istream& is, Magazine& magazine)
{
    //cout << "operator>>(istream& is, Magazine& magazine)" << endl;
    string title;
    int year, month, total;
    is >> title >> year >> month >> total;
    magazine = Magazine(title, total, year, month);
    //cout << "opeartor>> end" <<endl;
    return is;
}

/*** Library definition ***/
void Library::AddBookTitle(string title)
{
    book_titles_.push_back(title);
}

void Library::AddMagazineTitle(string title)
{
    magazine_titles_.push_back(title);
}

void Library::AddMagazine(string title, int num, int year, int month)
{
    map<string, Magazine>::iterator it = magazines_.find(title);
    if(it == magazines_.end())
    {
        Magazine temp(title, num, year, month);
        magazines_.insert(make_pair(temp.title(), temp));
        AddMagazineTitle(temp.title());
    }
    else
        it -> second.addtotal(num);
}

void Library::AddBook(string title, int num)
{
    map<string, Book>::iterator it = books_.find(title);
    if(it == books_.end())
    {
        books_.insert(make_pair(title, Book(title, num)));
        AddBookTitle(title);
    }
    else
        it -> second.addtotal(num);
}

void Library::DeleteTitle(const string& title)
{
    size_t i;
    for(i=0;i<book_titles_.size();i++)
        if(book_titles_[i] == title)    break;
    if(i<book_titles_.size())  book_titles_.erase(book_titles_.begin()+i);
    for(i=0;i<magazine_titles_.size();i++)
        if(magazine_titles_[i] == title)    break;
    if(i<magazine_titles_.size())   magazine_titles_.erase(magazine_titles_.begin()+i);

}

void Library::DeleteBook(const string& title)
{
    map<string, Book>::iterator it = books_.find(title);
    if(it != books_.end())
    {
        DeleteTitle(title);
        books_.erase(it);
    }
    map<string, Magazine>::iterator jt = magazines_.find(title);
    if(jt != magazines_.end())
    {
        DeleteTitle(title);
        magazines_.erase(jt);
    }
}

void Library::Lend(const string& title)
{
    map<string, Book>::iterator it = books_.find(title);
    bool flag = false;
    if(it != books_.end())
    {
        flag = !it->second.Lend();
        if(flag)  cout << "out of stock." << endl;
    }
    else
    {
        map<string, Magazine>::iterator jt = magazines_.find(title);
        if(jt != magazines_.end())
        {
            if(!jt->second.Lend())  cout << "out of stock." << endl;
        }
        else
            cout << "invalid operation." << endl;
    }
}

void Library::Return(const string& title)
{
    map<string, Book>::iterator it = books_.find(title);
    bool flag = false;
    if(it != books_.end())
    {
        flag = !it->second.Return();
        if(flag)   cout << "invalid operation." << endl;
    }
    else
    {
        map<string, Magazine>::iterator jt = magazines_.find(title);
        if(jt != magazines_.end())
        {
            if(!jt->second.Return())   cout << "invalid operation." << endl;
        }
        else
            cout << "invalid operation." << endl;
    }
}

void Library::PrintAll()
{
    string title;
    for(size_t i=0;i<book_titles_.size();i++)
    {
        title = book_titles_[i];
        map<string, Book>::const_iterator bit = books_.find(title);
        if(bit != books_.end()) printf("%d/%d %s\n", bit->second.stock(), bit->second.total(), bit->first.c_str());

    }
    for(size_t i=0;i<magazine_titles_.size();i++)
    {
        title = magazine_titles_[i];
        map<string, Magazine>::const_iterator mit = magazines_.find(title);
        if(mit != magazines_.end())
            printf("%d/%d %s\n", mit->second.stock(), mit->second.total(), mit->second.title().c_str());
    }
}
