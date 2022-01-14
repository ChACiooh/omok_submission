#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Book {
 public:
  Book()
  {
      total_ = stock_ = 0;
      title_ = "";
  }
  Book(const Book& book);
  Book(string title, int total);
  virtual string title() const { return title_; }
  int total() const { return total_; }  // 해당 도서의 총 보유 권수
  int stock() const { return stock_; }  // 도서의 재고 (남아있는 권수)
  void SetTitle(string title)   { title_ = title; }
  void SetTotal(int num)    { total_ = num; }
  void SetStock(int num)    { stock_ = num; }
  void addtotal(int num);
  void addstock(int num);
  bool Lend(int count);
  bool Return(int count);

 /*protected:
  string title_;
  int total_;
  int stock_;*/

 private:
  // 멤버변수를 정의.
  string title_;
  int total_;
  int stock_;
};

class Magazine : public Book {
 public:
  Magazine() { year_ = month_ = 0; }
  Magazine(const Magazine& magazine);
  Magazine(string title, int total, int year, int month);
  int year() const { return year_; }
  int month() const { return month_; }
  // 잡지의 제목 'PCMagazine(13/9)' 처럼 년/월을 원래 제목에 추가하여 리턴.
  string title() const;

 private:
  int year_;
  int month_;
};

// Input을 처리하는 operator 구현.
istream& operator>>(istream& is, Book& book);
istream& operator>>(istream& is, Magazine& magazine);

class Library {
 public:
  Library() {}
  // 도서 정보를 추가하는 함수
  void AddMagazine(string title, int num, int year, int month);
  void AddBook(string title, int num);
  // 도서 정보를 삭제하는 함수
  void DeleteTitle(const string& title);
  void DeleteBook(const string& title);

  void Lend(const string& title); // 책 한권을 대여하는 함수
  void Return(const string& title); // 책 한권을 반납하는 함수
  void PrintAll(); // 현재 저장되어 있는 도서(책과 잡지)의 리스트를 출력.
                   // 출력형식: stock/total title
 private:
  map<string, Book> books_;  // 도서를 저장하는 배열
  map<string, Magazine> magazines_;  // 잡지를 저장하는 배열
  vector<string> book_titles_, magazine_titles_;
  void AddBookTitle(string title);
  void AddMagazineTitle(string title);
};

#endif // LIBRARY_H_INCLUDED
