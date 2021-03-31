#include "Board.hpp"

void ariel::Board::post(unsigned int row, unsigned int column, Direction direction, string text)
{
	const unsigned int length = text.size();

	init(row, column, direction, length);

	if (direction == Direction::Horizontal) {
		for (unsigned int i = column; i < column + length; ++i) {
			_board[row][i] = text[i - column];
		}
	}
	else {
		for (unsigned int i = row; i < row + length; ++i) {
			_board[i][column] = text[i - row];
		}
	}
}

string ariel::Board::read(unsigned int row, unsigned int column, Direction direction, unsigned int length)
{
	/*
	init(row, column, direction, length);

	string result = "";

	if (direction == Direction::Horizontal) {
		result = _board[row].substr(column, length);
	}
	else {
		for (int i = row; i < row + length; ++i) {
			result += _board[i][column];
		}
	}

	return result;
	*/

	#pragma region optimized

	string result = "";

	if (length == 0) {
		return "";
	}

	if (_board.empty()) {
		return getFill((int)length);
	}

	if (direction == Direction::Horizontal) {
		if (_max_row < row) {
			return getFill((int)length);
		}

		if (_max_col < column + length - 1) {
			for (unsigned int i = column; i <= _max_col; ++i) {
				result += _board[row][i];
				--length;
			}

			result.append(getFill((int)length));
		}
		else {
			return _board[row].substr(column, length);
		}
	}
	else {
		if (_max_col < column) {
			return getFill((int)length);
		}

		if (_max_row < row + length - 1) {
			for (unsigned int i = row; i <= _max_row; ++i) {
				result += _board[i][column];
				--length;
			}

			result.append(getFill((int)length));
		}
		else {
			for (unsigned int i = row; i < row + length; ++i) {
				result += _board[i][column];
			}
		}
	}


	return result;

	#pragma endregion
}

void ariel::Board::show()
{
	for (unsigned int i = 0; i < _board.size(); ++i) {
		cout << _board[i] << endl;
	}
}



void ariel::Board::init(unsigned int row, unsigned int column)
{
	string str = getFill((int)column + 1);

	for (unsigned int i = 0; i <= row; ++i) {
		_board.push_back(str);
	}

	_max_row = row;
	_max_col = column;
}

void ariel::Board::init(unsigned int row, unsigned int column, Direction direction, unsigned int length)
{
	if (_board.empty()) {
		if (direction == Direction::Horizontal) {
			this->init(row, column + length - 1);
		}
		else {
			this->init(row + length - 1, column);
		}
	}

	if (direction == Direction::Horizontal) {
		const int col_dif = (int)(column + length - 1 - _max_col);

		// we need to allocate more columns
		if (col_dif > 0) {
			string str = getFill(col_dif);

			for (unsigned int i = 0; i <= _max_row; ++i) {
				_board[i].append(str);
			}

			_max_col = column + length - 1;
		}

		const int row_dif = (int)(row - _max_row);

		// we need to allocate more rows
		if (row_dif > 0) {
			string str = getFill((int)_max_col + 1);

			for (unsigned int i = 0; i < row_dif; ++i) {
				_board.push_back(str);
			}

			_max_row = row;
		}
	}
	else {
		const int col_dif = (int)(column - _max_col);

		// we need to allocate more columns
		if (col_dif > 0) {
			string str = getFill(col_dif);

			for (unsigned int i = 0; i <= _max_row; ++i) {
				_board[i].append(str);
			}

			_max_col = column;
		}

		const int row_dif = (int)(row + length - 1 - _max_row);

		// we need to allocate more rows
		if (row_dif > 0) {
			string str = getFill((int)_max_col + 1);

			for (unsigned int i = 0; i < row_dif; ++i) {
				_board.push_back(str);
			}

			_max_row = row + length - 1;
		}
	}
}

string ariel::Board::getFill(int length)
{
	string result = "";

	for (unsigned int i = 0; i < length; ++i) {
		result.append("_");
	}

	return result;
}


