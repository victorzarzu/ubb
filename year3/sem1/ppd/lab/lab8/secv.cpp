#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <fstream>

using namespace std;

vector<string> get_all_filenames(const string& dir, const int& no_countries, const int& no_probs) {
    vector<string> filenames;

    for(int i = 1;i <= no_countries;++i) {
        for(int j = 1;j <= no_probs;++j) {
            stringstream filename;
            filename << dir << "/Rezultate" <<i << "_" << j << ".txt";
            filenames.push_back(filename.str());
        }
    }

    return filenames;
}

struct Node {
    int id, score;
    Node* next;

    Node(int _id, int _score) {
        id = _id;
        score = _score;
        next = nullptr;
    }
    Node() {
        id = score = 0;
        next = nullptr;
    }
};

class LinkedList {
    private:
        Node* root = nullptr;
    
        Node* removeNode(const int& id) {
            if(this->root == nullptr) {
                return nullptr;
            }
            if(root->id == id) {
                Node* node = root;
                root = root->next;
                return node;
            }
            Node* node = root;
            while(node->next != nullptr && node->next->id != id) {
                node = node->next;
            }
            if(node->next == nullptr || node->next->id != id) {
                return nullptr;
            }
            if(node->next->score == -1) {
                return node->next;
            }

            Node* result_node = node->next;
            node->next = node->next->next;
            return result_node;
        }
    public:
        void add(const int& id, const int& score) {
            Node* node = this->removeNode(id);
            if(node == nullptr) {
                node = new Node(id, score);
            } else if(node->score == -1) {
                return;
            } else if(score == -1) {
                node->score = score;
            } else {
                node->score += score;
            }
            if(this->root == nullptr) {
                this->root = node;
                return;
            }
            if(node->score > this->root->score) {
                node->next = this->root;
                this->root = node;
                return;
            }
            Node* current_node = this->root;
            while(current_node->next && (current_node->next->score > node->score || (current_node->next->score == node->score && node->id < current_node->next->id))) {
                current_node = current_node->next;
            }
            node->next = current_node->next;
            current_node->next = node;
        }

        void print(const string& filename) {
            ofstream g(filename);
            Node* node = this->root;
            while(node) {
                g<<node->id<<" "<<node->score<<'\n';
                node = node->next;
            }
            g.close();
        }

        ~LinkedList() {
            Node* current = root;
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }

};

int main(int argc, char **argv) {
    if(argc != 5) {
        cout<<"Incorrect number of parameters: <directory> <no_countries> <no_probs> <output_file>";
        return 0;
    }
    string dir(argv[1]);
    int no_countries = atoi(argv[2]);
    int no_probs = atoi(argv[3]);
    string output_file(argv[4]);

    auto start = std::chrono::high_resolution_clock::now();

    LinkedList list = LinkedList();
    for(const auto& filename : get_all_filenames(dir, no_countries, no_probs)) {
        int id, score;
        ifstream f(filename);
        while(f>>id>>score) {
            list.add(id, score);
        }

        f.close();
    }
    list.print(output_file);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Execution Time: " << duration.count() << " milliseconds" << '\n' << std::flush;

    return 0;
}