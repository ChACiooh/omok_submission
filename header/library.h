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
  int total() const { return total_; }  // �ش� ������ �� ���� �Ǽ�
  int stock() const { return stock_; }  // ������ ��� (�����ִ� �Ǽ�)
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
  // ��������� ����.
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
  // ������ ���� 'PCMagazine(13/9)' ó�� ��/���� ���� ���� �߰��Ͽ� ����.
  string title() const;

 private:
  int year_;
  int month_;
};

// Input�� ó���ϴ� operator ����.
istream& operator>>(istream& is, Book& book);
istream& operator>>(istream& is, Magazine& magazine);

class Library {
 public:
  Library() {}
  // ���� ������ �߰��ϴ� �Լ�
  void AddMagazine(string title, int num, int year, int month);
  void AddBook(string title, int num);
  // ���� ������ �����ϴ� �Լ�
  void DeleteTitle(const string& title);
  void DeleteBook(const string& title);

  void Lend(const string& title); // å �ѱ��� �뿩�ϴ� �Լ�
  void Return(const string& title); // å �ѱ��� �ݳ��ϴ� �Լ�
  void PrintAll(); // ���� ����Ǿ� �ִ� ����(å�� ����)�� ����Ʈ�� ���.
                   // �������: stock/total title
 private:
  map<string, Book> books_;  // ������ �����ϴ� �迭
  map<string, Magazine> magazines_;  // ������ �����ϴ� �迭
  vector<string> book_titles_, magazine_titles_;
  void AddBookTitle(string title);
  void AddMagazineTitle(string title);
};

#endif // LIBRARY_H_INCLUDED
