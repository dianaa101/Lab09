#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>
#include <string>
#include <utility>

using std::string;
using std::exception;

class RepoException : public exception {
	string mesaj;

public:
	explicit RepoException(string mesaj) : mesaj{ move(mesaj) } {};
	string get_mesaj() { return this->mesaj; }
};

class ValidatorException : public exception {
	string mesaj;
public:
	explicit ValidatorException(string mesaj) : mesaj(move(mesaj)) {};
	string get_mesaj() { return this->mesaj; }
};

class NotificareException : public exception {
	string mesaj;
public:
	explicit NotificareException(string mesaj) noexcept : mesaj(move(mesaj)) {};
	string get_mesaj() { return this->mesaj;  }
};

class BadLuckException : public exception {
	string mesaj;
public:
	explicit BadLuckException(string mesaj) noexcept : mesaj(move(mesaj)) {};
	string get_mesaj() { return this->mesaj; }
};

#endif /* EXCEPTION_H_ */
