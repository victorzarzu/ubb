#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <mutex>
#include <queue>
#include <tuple>
#include <thread>
#include <functional>
#include <barrier>
#include <functional>
#include "synced_queue.h"

using namespace std;

#define participant pair<int, int>
#define id first
#define score second

SyncedQueue<string> get_all_filenames(const string& dir, const int& no_countries, const int& no_probs) {
    SyncedQueue<string> filenames;

    for(int i = 1;i <= no_countries;++i) {
        for(int j = 1;j <= no_probs;++j) {
            stringstream filename;
            filename << dir << "/Rezultate" <<i << "_" << j << ".txt";
            filenames.push(filename.str());
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
        mutex m;
        int length = 0;
    
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
            m.lock();
            this->length++;
            Node* node = this->removeNode(id);
            if(node == nullptr) {
                node = new Node(id, score);
            } else if(node->score == -1) {
                m.unlock();
                return;
            } else if(score == -1) {
                node->score = score;
            } else {
                node->score += score;
            }
            if(this->root == nullptr) {
                this->root = node;
                m.unlock();
                return;
            }
            if(node->score > this->root->score) {
                node->next = this->root;
                this->root = node;
                m.unlock();
                return;
            }
            Node* current_node = this->root;
            while(current_node->next && (current_node->next->score > node->score || (current_node->next->score == node->score && node->id < current_node->next->id))) {
                current_node = current_node->next;
            }
            node->next = current_node->next;
            current_node->next = node;
            m.unlock();
        }

        void print(const string& filename) {
            m.lock();
            ofstream g(filename);
            Node* node = this->root;
            while(node) {
                g<<node->id<<" "<<node->score<<'\n';
                node = node->next;
            }
            g.close();
            m.unlock();
        }

        int size() {
            m.lock();
            int result = this->length;
            m.unlock();
            return result;
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

void read_run(SyncedQueue<string>& filenames, SyncedQueue<participant>& participants, std::barrier<std::function<void()>>& barrier, std::barrier<std::function<void()>>& read_barrier, const int& index, LinkedList* list, const string& output_file) {
    while(filenames.size()) {
        string filename = filenames.pop();
        ifstream f(filename);
        int id, score;
        while(f>>id>>score) {
            participants.push(make_pair(id, score));
        }
        f.close();
    }
    read_barrier.arrive_and_wait();
    participants.setFinished();
    barrier.arrive_and_wait();
    if(index == 1) {
        list->print(output_file);
    }
}

void write_run(LinkedList* list, SyncedQueue<participant>& participants, const int& total_size, std::barrier<std::function<void()>>& barrier, const int& index) {
    while(true) {
        participant part = participants.pop();
        if(part == participant()) {
            break;
        }
        list->add(part.id, part.score);
    }
    cout<<"gata " << index<<'\n';
    barrier.arrive_and_wait();
}


int main(int argc, char **argv) {
    if(argc != 6) {
        cout<<"Incorrect number of parameters: <directory> <no_countries> <no_probs> <output_file> <no_threads>";
        return 0;
    }
    string dir(argv[1]);
    int no_countries = atoi(argv[2]);
    int no_probs = atoi(argv[3]);
    string output_file(argv[4]);
    int no_threads = atoi(argv[5]);

    auto start = std::chrono::high_resolution_clock::now();
    int no_read_threads = no_threads / 2;
    int no_write_threads = no_threads - no_read_threads;
    std::barrier<std::function<void()>> barrier(no_threads, []() noexcept {return;});
    std::barrier<std::function<void()>> read_barrier(no_read_threads, []() noexcept {return;});
    SyncedQueue<string> filenames = get_all_filenames(dir, no_countries, no_probs);
    SyncedQueue<participant> participants;
    LinkedList* list = new LinkedList();

    vector<thread> threads;
    for(int i = 1;i <= no_threads;++i) {
        if(i <= no_read_threads) {
            threads.push_back(thread(read_run, std::ref(filenames), std::ref(participants), ref(barrier), ref(read_barrier), i, list, output_file));
        } else {
            threads.push_back(thread(write_run, std::ref(list), std::ref(participants), no_countries * no_probs * 100, ref(barrier), i));
        }
    }

    for(auto& thread : threads) {
        thread.join();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    cout << "Execution Time: " << duration.count() << " milliseconds" << '\n' << std::flush;

    return 0;
}