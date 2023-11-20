#ifndef SYNCED_QUEUE
#define SYNCED_QUEUE

#include <queue>
#include <mutex>

template<class T> 
class SyncedQueue {
    private:
        int max_dim = 50;
        std::queue<T> q;
        std::condition_variable full;
        std::condition_variable empty;
        std::mutex m;
        bool finished = false;
    public:
        SyncedQueue() {}
        SyncedQueue(const int& max_dim) {
            this->max_dim = max_dim;
        }

        SyncedQueue(const SyncedQueue& other) {
            this->max_dim = other.max_dim;
            this->q = other.q;
        }

        void push(T element) {
            std::unique_lock lk(m);
            full.wait(lk, [&] {return this->q.size() < max_dim; });
            q.push(element);
            lk.unlock();
            empty.notify_all();
        }

        T pop() {
            std::unique_lock lk(m);
            if(finished && q.size() == 0) {
                return T();
            }
            empty.wait(lk, [&] {return this->q.size() > 0; });
            T result = q.front();
            q.pop();
            lk.unlock();
            full.notify_all();
            return result;
        }

        int size() {
            std::unique_lock lk(m);
            int size = q.size();
            lk.unlock();
            return size;
        }

        void setFinished() {
            std::unique_lock lk(m);
            this->finished = true;
            lk.unlock();
        }

};

#endif