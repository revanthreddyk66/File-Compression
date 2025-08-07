// File Compression System using Huffman Coding Algorithm
// Features: Build Huffman Tree, Generate Codes, Compress/Decompress Files

#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <bitset>
#include <memory>
#include <vector>

using namespace std;

// ========================= HUFFMAN TREE NODE =========================
struct HuffmanNode {
    char character;
    int frequency;
    shared_ptr<HuffmanNode> left, right;
    
    HuffmanNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
    HuffmanNode(int freq) : character('\0'), frequency(freq), left(nullptr), right(nullptr) {}
};

// Comparator for priority queue (min-heap based on frequency)
struct Compare {
    bool operator()(shared_ptr<HuffmanNode> a, shared_ptr<HuffmanNode> b) {
        if (a->frequency == b->frequency) {
            return a->character > b->character; // Tie-breaking for consistent results
        }
        return a->frequency > b->frequency;
    }
};

// ========================= HUFFMAN COMPRESSION ENGINE =========================
class HuffmanCompressor {
private:
    unordered_map<char, int> frequencyTable;
    unordered_map<char, string> huffmanCodes;
    shared_ptr<HuffmanNode> root;
    
    // Build frequency table from input text
    void buildFrequencyTable(const string& text) {
        frequencyTable.clear();
        for (char ch : text) {
            frequencyTable[ch]++;
        }
        cout << "📊 Frequency Analysis Complete: " << frequencyTable.size() << " unique characters" << endl;
    }
    
    // Build Huffman Tree using greedy algorithm
    void buildHuffmanTree() {
        priority_queue<shared_ptr<HuffmanNode>, vector<shared_ptr<HuffmanNode>>, Compare> minHeap;
        
        // Create leaf nodes for each character
        for (auto& pair : frequencyTable) {
            minHeap.push(make_shared<HuffmanNode>(pair.first, pair.second));
        }
        
        // Build tree bottom-up
        while (minHeap.size() > 1) {
            auto left = minHeap.top(); minHeap.pop();
            auto right = minHeap.top(); minHeap.pop();
            
            auto merged = make_shared<HuffmanNode>(left->frequency + right->frequency);
            merged->left = left;
            merged->right = right;
            minHeap.push(merged);
        }
        
        root = minHeap.empty() ? nullptr : minHeap.top();
        cout << "🌳 Huffman Tree Built Successfully" << endl;
    }
    
    // Generate binary codes for each character
    void generateCodes(shared_ptr<HuffmanNode> node, string code) {
        if (!node) return;
        
        // Leaf node - store the code
        if (!node->left && !node->right) {
            huffmanCodes[node->character] = code.empty() ? "0" : code;
            return;
        }
        
        generateCodes(node->left, code + "0");
        generateCodes(node->right, code + "1");
    }
    
public:
    // Main compression function
    string compress(const string& text) {
        if (text.empty()) return "";
        
        cout << "\n🗜️  Starting Compression Process..." << endl;
        cout << "📝 Original Text Length: " << text.length() << " characters" << endl;
        
        // Step 1: Analyze character frequencies
        buildFrequencyTable(text);
        
        // Step 2: Build optimal Huffman tree
        buildHuffmanTree();
        
        // Step 3: Generate binary codes
        huffmanCodes.clear();
        generateCodes(root, "");
        
        // Step 4: Encode the text
        string compressedData = "";
        for (char ch : text) {
            compressedData += huffmanCodes[ch];
        }
        
        // Calculate compression statistics
        double compressionRatio = (double)compressedData.length() / (text.length() * 8) * 100;
        cout << "✅ Compression Complete!" << endl;
        cout << "📊 Compressed Size: " << compressedData.length() << " bits" << endl;
        cout << "📈 Compression Ratio: " << fixed << setprecision(1) << compressionRatio << "%" << endl;
        cout << "💾 Space Saved: " << fixed << setprecision(1) << (100 - compressionRatio) << "%" << endl;
        
        return compressedData;
    }
    
    // Decompression function
    string decompress(const string& compressedData) {
        if (compressedData.empty() || !root) return "";
        
        cout << "\n📂 Starting Decompression Process..." << endl;
        
        string decompressedText = "";
        auto currentNode = root;
        
        for (char bit : compressedData) {
            // Traverse tree based on bit
            if (bit == '0') {
                currentNode = currentNode->left;
            } else {
                currentNode = currentNode->right;
            }
            
            // Reached leaf node - found character
            if (!currentNode->left && !currentNode->right) {
                decompressedText += currentNode->character;
                currentNode = root; // Reset to root for next character
            }
        }
        
        cout << "✅ Decompression Complete!" << endl;
        cout << "📄 Recovered Text Length: " << decompressedText.length() << " characters" << endl;
        
        return decompressedText;
    }
    
    // Display generated Huffman codes
    void displayCodes() {
        cout << "\n🔢 Generated Huffman Codes:" << endl;
        cout << string(30, '-') << endl;
        for (auto& pair : huffmanCodes) {
            char ch = pair.first;
            string displayChar = (ch == ' ') ? "SPACE" : 
                                (ch == '\n') ? "NEWLINE" : 
                                (ch == '\t') ? "TAB" : string(1, ch);
            cout << displayChar << " -> " << pair.second << 
                    " (freq: " << frequencyTable[ch] << ")" << endl;
        }
    }
};

// ========================= FILE I/O OPERATIONS =========================
class FileManager {
public:
    static string readFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "❌ Error: Could not open file " << filename << endl;
            return "";
        }
        
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        cout << "📖 File '" << filename << "' loaded successfully" << endl;
        return content;
    }
    
    static bool writeFile(const string& filename, const string& content) {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "❌ Error: Could not create file " << filename << endl;
            return false;
        }
        
        file << content;
        file.close();
        cout << "💾 File '" << filename << "' saved successfully" << endl;
        return true;
    }
};

// ========================= DEMO AND TESTING =========================
int main() {
    cout << "🚀 Huffman Coding File Compression System" << endl;
    cout << string(50, '=') << endl;
    
    HuffmanCompressor compressor;
    
    // Test with sample text
    string originalText = "ABRACADABRA! This is a test of Huffman coding compression algorithm. "
                         "The quick brown fox jumps over the lazy dog. Compression efficiency depends on character frequency distribution.";
    
    cout << "\n📝 Original Text:" << endl;
    cout << "\"" << originalText << "\"" << endl;
    
    // Compress the text
    string compressed = compressor.compress(originalText);
    
    // Show the generated codes
    compressor.displayCodes();
    
    // Decompress and verify
    string decompressed = compressor.decompress(compressed);
    
    cout << "\n🔍 Verification:" << endl;
    cout << "Original:     \"" << originalText.substr(0, 50) << "...\"" << endl;
    cout << "Decompressed: \"" << decompressed.substr(0, 50) << "...\"" << endl;
    cout << "✅ Match: " << (originalText == decompressed ? "SUCCESS" : "FAILED") << endl;
    
    // File operations demo
    cout << "\n💾 File Operations Demo:" << endl;
    FileManager::writeFile("sample.txt", originalText);
    FileManager::writeFile("compressed.bin", compressed);
    
    string loadedText = FileManager::readFile("sample.txt");
    if (!loadedText.empty()) {
        cout << "📁 File compression workflow completed successfully!" << endl;
    }
    
    return 0;
}
