#ifndef __WHISKEY_Core_LiteralPrinterInt_HPP
#define __WHISKEY_Core_LiteralPrinterInt_HPP

#include <whiskey/Core/Module.inc>

namespace whiskey {
template<typename T>
class LiteralPrinterInt {
private:
	T value;
	unsigned int base;
	bool usePrefix;
	unsigned int width;

protected:
	virtual void onPrint(std::ostream &os) const;

public:
	static bool isValidBase(unsigned int base);
	static void printBasePrefix(unsigned int base, std::ostream &os);
	static unsigned int getNDigits(T value, unsigned int base);

	LiteralPrinterInt(T value, unsigned int base = 10, bool usePrefix = true, unsigned int width = 0);
	virtual ~LiteralPrinterInt();

	T getValue() const;
	void setValue(T value);

	unsigned int getBase() const;
	void setBase(unsigned int value);

	bool getUsePrefix() const;
	void setUsePrefix(bool value);

	unsigned int getWidth() const;
	void setWidth(unsigned int value);

	void print(std::ostream &os) const;
};
}

#include <whiskey/Core/LiteralPrinterInt.tpp>

#endif
