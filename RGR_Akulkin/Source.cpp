#include "Ciphers.h"
#include <Windows.h>
//test
int CipherSelection() {
	cout << "Choose a cipher:\n";
	cout << "1) Atbash;\n";
	cout << "2) RSA;\n";
	cout << "3) Rail Fence Chipher;\n";
	cout << "4) Exit to main menu.\n";
	cout << "Enter a number from 1 to 4: ";

	int cipher_selection;
	cipher_selection = ReadInt();
	cout << endl;
	if (cipher_selection < 1 || cipher_selection > 4) throw "ERROR: Incorrect input. The number does not match the specified range.";
	return cipher_selection;
}

bool PassVerif(string const& password) {
	string input;
	cout << "Enter the password: ";
	cin.clear();
	getline(cin, input);
	cout << endl;

	if (input.length() != password.length()) {
		return false;
	}
	else {
		for (int i = 0; i < password.length(); i++) {
			if (input[i] != password[i]) return false;
		}
	}
	return true;
}

enum MENU { ENTER_TEXT = 1, ENCODE_DECODE, ENCODE, DECODE, OUTPUT_TEXT, EXIT };
enum CHIPHER { ATBASH = 1, RSA, RAIL_FENCE, MAIN_EXIT };

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	string str = "ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß";
	for (int i = 0; i < str.length(); i++) {
		cout << int(str[i]) << " ";
	}
	cout << endl;

	string file_directory = "C://Users//nikit//Desktop//FILE.txt";
	string program_password = "1111";

	while (true) {
		try {
			cout << "Select an action:\n";
			cout << "1) Entering text into a file;\n";
			cout << "2) Encode-Decode text;\n";
			cout << "3) Encode text;\n";
			cout << "4) Decode text;\n";
			cout << "5) Text output from a file;\n";
			cout << "6) Exit.\n";
			cout << "Enter a number from 1 to 6: ";

			int action_selection;
			action_selection = ReadInt();
			cout << endl;
			if (action_selection < 1 || action_selection > 6) throw "ERROR: Incorrect input. The number does not match the specified range.";

			string file_text;
			switch (action_selection) {
			case ENTER_TEXT:
				cin.clear();
				getline(cin, file_text);
				cout << endl;
				FileInput(file_directory, file_text);
				break;

			case ENCODE_DECODE:
				if (!PassVerif(program_password)) {
					throw "ERROR: Incorrect password.";
				}
				else {
					switch (CipherSelection()) {
					case ATBASH:
						cout << "Input text: ";
						cin.clear();
						getline(cin, file_text);
						cout << endl;
						FileInput(file_directory, file_text);

						AtbashEnDecode(file_directory);

						cout << "Encrypted text: " << FileOutput(file_directory) << "\n\n";

						AtbashEnDecode(file_directory);
						break;

					case RSA:
						cout << "Input text: ";
						cin.clear();
						getline(cin, file_text);
						cout << endl;
						FileInput(file_directory, file_text);

						RSA_Encode(file_directory);

						cout << "Encrypted text: " << FileOutput(file_directory) << "\n\n";

						RSA_Decode(file_directory);
						break;

					case RAIL_FENCE:
						cout << "Input text: ";
						cin.clear();
						getline(cin, file_text);
						cout << endl;
						FileInput(file_directory, file_text);

						RailFenceEncode(file_directory);

						cout << "Encrypted text: " << FileOutput(file_directory) << "\n\n";

						RailFenceDecode(file_directory);
						break;

					case MAIN_EXIT:
						break;
					}

					cout << "Decrypted text: " << FileOutput(file_directory) << "\n\n";
				}
				break;

			case ENCODE:
				if (!PassVerif(program_password)) {
					throw "ERROR: Incorrect password.";
				}
				else {
					switch (CipherSelection()) {
					case ATBASH:
						AtbashEnDecode(file_directory);
						break;

					case RSA:
						RSA_Encode(file_directory);
						break;

					case RAIL_FENCE:
						RailFenceEncode(file_directory);
						break;

					case MAIN_EXIT:
						break;
					}
				}
				break;

			case DECODE:
				if (!PassVerif(program_password)) {
					throw "ERROR: Incorrect password.";
				}
				else {
					switch (CipherSelection()) {
					case ATBASH:
						AtbashEnDecode(file_directory);
						break;

					case RSA:
						RSA_Decode(file_directory);
						break;

					case RAIL_FENCE:
						RailFenceDecode(file_directory);
						break;

					case MAIN_EXIT:
						break;
					}
				}
				break;

			case OUTPUT_TEXT:
				file_text = FileOutput(file_directory);
				cout << file_text << "\n\n";
				break;

			case EXIT:
				exit(0);
				break;
			}

		}

		catch (const char* msg) {
			cout << msg << "\n\n";
		}
	}
}