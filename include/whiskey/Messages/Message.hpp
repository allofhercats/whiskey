#ifndef __WHISKEY_Messages_Message_HPP
#define __WHISKEY_Messages_Message_HPP

#include <whiskey/Messages/Module.inc>

namespace whiskey {
class Message {
public:
	enum ID {
		CannotOpen,
		UnexpectedChar,
		MismatchedBlockComments,
		ExclamationPointAlone,
		MismatchedSingleQuotes,
		MismatchedDoubleQuotes,
		UnexpectedToken
	};

	enum Severity {
		Note,
		Warning,
		Error,
		FatalError,
		InternalCompilerError
	};

	static Severity getSeverity(ID id);

private:
	Range range;
	ID id;
	std::string desc;

public:
	Message(Range range, ID id, std::string desc);

	Range &getRange();
	const Range &getRange() const;
	void setRange(Range value);

	ID getID() const;
	void setID(ID value);

	const std::string &getDesc() const;
	void setDesc(std::string value);

	void print(std::ostream &os) const;
};
}

#endif
