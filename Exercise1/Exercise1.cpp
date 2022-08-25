#include <iostream>
#include <algorithm>

void decryptMessage(char* message, char* freqLang);
char decryptCharacter(char c, std::pair <int, int>* lettersCounter, char* freqLang);

int main()
{
	char message[] = "Bgc-bfufb tegaedppqna ql aggv zge xof tegaedppfe'l lgjb.\
	\nXof adpf vflqanfe logjbvn'x hf pdwqna d cgebv qn coqro xof tbdkfe ql mjlx d lpdbb tdex. Xof tbdkfe QL XOF HGLL; qx'l kgje vjxk xg fnxfexdqn oqp ge ofe.\
	\nZgrjl ql d pdxxfe gz vfrqvqna codx xoqnal kgj def ngx agqna xg vg.\
	\nXof rglx gz dvvqna d zfdxjef qln'x mjlx xof xqpf qx xdwfl xg rgvf qx. Xof rglx dblg qnrbjvfl xof dvvqxqgn gz dn ghlxdrbf xg zjxjef fstdnlqgn. Xof xeqrw ql xg tqrw xof zfdxjefl xodx vgn'x zqaox fdro gxofe. - Mgon Rdepdrw.\
	\n(ccc.adpdljxed.rgp/uqfc/nfcl/234346?utkjpvbjr)\
	\n(ccc.hedqnkijgxf.rgp/ijgxfl/djxogel/m/mgon_rdepdrw.oxpb)";

	char freqLang[] = "TEOAISRHNUCMDLGWFPYKJBVQX";

	decryptMessage(message, freqLang);

}


//Only A-Z characters can be decrypted
bool shouldDecryptCharacter(char x) {
	return (x >= 'A' && x <= 'Z') || (x <= 'z' && x >= 'a');
}

//Decrypt and print the message
void decryptMessage(char* message, char* freqLang) {

	std::pair <int, int> lettersCounter[26];

	//Each pair contains the alphabet letter and the number of times the letter appears in the message
	for (int i = 0; i < 26 ; i++) {
		lettersCounter[i].first = i + 'a';
	}
	for (int i = 0; i < (int) strlen(message); i++) {
		if (shouldDecryptCharacter(message[i])) {		
			int index = tolower(message[i])-'a';
			lettersCounter[index].second++;
		}
	}
	
	//Sorting the pair array by letter ocurrence
	std::sort(std::begin(lettersCounter), std::end(lettersCounter), [](auto &left, auto &right) {
		return left.second > right.second;
	});


	//Decrypt every letter of the message using the lettersCounter array and the freqLang param
	for (int i = 0; i < (int)strlen(message); i++) {
		
		if (shouldDecryptCharacter(message[i])) {
			message[i] = decryptCharacter(message[i], lettersCounter, freqLang);
		}		
 
	}
	
	//Printing decrypted data
	std::cout << message << "\n";

}


//lettersCounter array contains the number of times each alphabet letter appears in the message sorted by ocurrence
char decryptCharacter(char c, std::pair <int, int>* lettersCounter, char* freqLang) 
{

	for (int i = 0; i < (int) strlen(freqLang); i++) {
		if (lettersCounter[i].first == tolower(c) ) {
			if (c >= 'A' && c<='Z') {
				return toupper(freqLang[i]);
			}
			else {
				return tolower(freqLang[i]);
			}					

		}
	}

	return 0;

}

