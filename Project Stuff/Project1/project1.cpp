#include <iostream>
#include <string>
using namespace std;

class Text2Compress
{
protected:
    int _seq[200000];    // stores the current sequence
    int _length;         // length of sequence
    int _freq[640][640]; // static matrix 128+k by 128+k
    int _rules[512][3];  // merge rules: a b -> z
    int _ruleCount;      // number of rules learned
    int _maxSymbol;      // highest assigned symbol ID

public:
    Text2Compress();
    void initialize(int k, int lines); // read input text
    void train(int k);                         // perform k merges
    void encode();                             // apply learned merges
    void decode();                             // optional: expand compressed form
    void displaySequence();                    // print current sequence
    void displayRules();                       // print learned rules
};

Text2Compress::Text2Compress() {
    
}

void Text2Compress::initialize(int k, int lines) {
    int seq_point = 0;
    int i = 0;
    while (i < lines) {
        if (cin.peek() == '\n') {
            // _seq[seq_point] = '\r'; 
            // seq_point++;
            _seq[seq_point] = cin.get(); 
            seq_point++;
            i++;
        }
        else{
        _seq[seq_point] = cin.get(); 
        seq_point++;
        }
    }
    _length = seq_point;
}

void Text2Compress::train(int k) {
    for (int j = 0; j < k; j++) {

        for (int a = 0; a < 640; a++) {
            for (int b = 0; b < 640; b++) {
                _freq[a][b] = 0;
            }
        }

        for (int i = 1; i < _length; i++) {
            _freq[_seq[i-1]][_seq[i]]++;
        }

        int max = 0;
        int pos1 = 0;
        int pos2 = 0;
        for (int a = 0; a < 128+k; a++) {
            for (int b = 0; b < 128+k; b++) {
                if (_freq[a][b] > max) {
                    pos1 = a;
                    pos2 = b;
                    max = _freq[a][b];
                }
            }
        }
        
        _rules[j][0] = pos1;
        _rules[j][1] = pos2;
        _rules[j][2] = 128+j;
        _ruleCount++;

        int prev = _seq[0];
        int curr = 0;
        int displacement = 0;
        int new_length = _length;
        for (int i = 1; i < _length; i++) {
            curr = _seq[i];
            if ((prev == pos1) && (curr == pos2)) {
                _seq[i-1-displacement] = 128+j;
                i++;
                if (i != _length) {
                prev = _seq[i];
                displacement++;
                }
                new_length--;
                
            }
            else {
                _seq[i-1-displacement] = prev;
                if (i == _length-1) {_seq[i-displacement] = curr;}
                prev = curr;
                
            }
            
        }
        _length = new_length;
         if (_length == 1) {
            break;
        }
    }

}

void Text2Compress::encode() {
    for (int j = 0; j < _ruleCount; j++) {
        int prev_rule = _rules[j][0];
        int curr_rule = _rules[j][1];
        int insert = _rules[j][2];
        int prev = _seq[0];
        int curr = 0;
        int displacement = 0;
        int new_length = _length;
        for (int i = 1; i < _length; i++) {
            curr = _seq[i];
            if ((prev == prev_rule) && (curr == curr_rule)) {
                _seq[i-1-displacement] = 128+j;
                i++;
                if (i != _length) {
                prev = _seq[i];
                displacement++;
                }
                new_length--;
                
            }
            else {
                _seq[i-1-displacement] = prev;
                if (i == _length-1) {_seq[i-displacement] = curr;}
                prev = curr;
                
            }
            
        }

    }

}

void Text2Compress::decode() {
    cout << "Decompressed Text:" << endl;
    int k;
    cin >> k;
    while (cin.peek() == '\r' || cin.peek() == '\n')
        {
            cin.get();
        }
    int rule1[1000], rule2[1000], ruleresult[1000];
    for (int i = 0; i < k; i++) {
        cin >> rule1[i] >> rule2[i] >> ruleresult[i];
        while (cin.peek() == '\r' || cin.peek() == '\n')
        {
            cin.get();
        }
    }
    int temp_seq[2000];
    int temp_length = 0;  
    bool special_case = false;
    while (cin.peek() != -1) {
        cin >> temp_seq[temp_length];
        temp_length++;
    }
    for (int i = k-1; i >= 0; i--) {        
        int backload[10000];
        int backlength = 0;
        int new_length = 0;
        for (int j = 0; j < temp_length; j++) {
            backload[backlength] = temp_seq[j];
            if (backload[0] == ruleresult[i]) {
                temp_seq[j] = rule1[i];
                backlength++;
                backload[backlength] = temp_seq[j+1];
                temp_seq[j+1] = rule2[i];
                if (j != temp_length-1) {
                    j++;
                }
                else{special_case = true;}
                new_length++;
            }
            else{
               temp_seq[j] = backload[0];
            }
            for (int t = 0; t < backlength; t++) {
                backload[t] = backload[t+1];
            }
            backload[backlength] = 0;
            new_length++;
            if ((j == temp_length-1) && backlength > 0) {
                if (special_case) {
                        j++;
                    }
                while (backload[0] != 0) {
                    backlength--;
                    j++;
                    if (backload[0] == ruleresult[i]) {
                        temp_seq[j] = rule1[i];
                        backlength++;
                        backload[backlength] = temp_seq[j+1];
                        temp_seq[j+1] = rule2[i];
                        j++;
                        new_length++;
                    }
                    else{
                        temp_seq[j] = backload[0];
                    }
                    for (int t = 0; t < backlength; t++) {
                        backload[t] = backload[t+1];
                    }
                    backload[backlength] = 0;
                    new_length++;
                }
            }

        }
        temp_length = new_length;
    }
    for (int i = 0; i < temp_length; i++) {
        cout << char(temp_seq[i]);
    }
}

void Text2Compress::displaySequence() {
    for (int i = 0; i < _length; i++) {
        cout << _seq[i] << " ";
    }
    cout << endl;

}

void Text2Compress::displayRules() {
    for (int i = 0; i < _ruleCount; i++) {
        cout << _rules[i][0] << " " << _rules[i][1] << " " << _rules[i][2] << endl;
    }
}

int main()
{
    int k, numLines;
    // First row: k and number of lines of input
    cin >> k >> numLines;
    while (cin.peek() == '\r' || cin.peek() == '\n')
    {
        cin.get(); // eat carriage returns and newlines
    }
    // Step 2: Create a Text2Compress object
    Text2Compress* compressor = new Text2Compress();
    
    compressor->initialize(k, numLines);

    // Step 3: Train with k merges
    compressor->train(k);
    // Step 4: Display the learned rules
    cout << "Rules learned from Compression:" << endl;
    compressor->displayRules();
    // Step 5: Display the compressed sequence
    cout << "Compressed sequence:" << endl;
    compressor->displaySequence();
    // Step 6: Process decompression lines (triplets + sequence)
    // You will write code to handle that part

    // Step7: print the compressed text
    compressor->decode();
    
    delete compressor;

    return 0;
}