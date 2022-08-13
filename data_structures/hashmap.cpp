#include <iostream>
#include <list>

template <typename Key, typename Value> class hash_map {
public:
  explicit hash_map(float max_load_factor_, size_t bucket_count_)
      : max_load_factor(max_load_factor_), m_bucket_count(bucket_count_) {
    // Create m_bucket_count buckets.
    // This is because we ideally want only one element per bucket.
    buckets = new std::list<std::pair<Key, Value>>[m_bucket_count];
  }

  ~hash_map() { delete[] buckets; }

  // Best case: O(1), Worst case: O(N), Amortized: O(1)
  void insert(Key key, Value val) {
    auto hash = find_hash(key);
    auto it = find(key);

    // if key is present, modify its value
    if (it != buckets[hash].end()) {
      it->second = val;
      return;
    }

    buckets[hash].emplace_back(key, val);
    num_elements++;

    rehash_if_needed();
  }

  // O(1)
  void erase(Key key) {
    auto hash = find_hash(key);
    auto it = find(key);

    if (it == buckets[hash].end()) {
      return;
    }

    buckets[hash].erase(it);
    num_elements--;
  }

  // Average case: O(1), Worst case: O(max number of elements in a bucket)
  typename std::list<std::pair<Key, Value>>::iterator find(Key key) const {
    auto hash = find_hash(key);

    // check the bucket corresponding to hash
    for (auto it = buckets[hash].begin(); it != buckets[hash].end(); it++) {
      if (it->first == key) {
        return it;
      }
    }
    return buckets[hash].end();
  }

  // O(N)
  void rehash() {
    std::cout << "Rehashing..." << std::endl;

    // create new buckets
    m_bucket_count *= 2;
    auto new_buckets = new std::list<std::pair<Key, Value>>[m_bucket_count];

    for (int i = 0; i < m_bucket_count / 2; i++) {
      // Distribute the data among new buckets
      for (auto it = buckets[i].begin(); it != buckets[i].end(); it++) {
        new_buckets[find_hash(it->first)].push_back(*it);
      }
    }

    delete[] buckets;
    buckets = new_buckets;
  }

  void display() const {
    for (int i = 0; i < m_bucket_count; i++) {
      std::cout << "Bucket: " << buckets[i].size() << std::endl;
    }
  }

  inline size_t size() const { return num_elements; }

  inline size_t bucket_count() const { return m_bucket_count; }

private:
  // O(1)
  inline int find_hash(Key key) const { return key % m_bucket_count; }

  void rehash_if_needed() {
    if ((num_elements / m_bucket_count) <= max_load_factor) {
      return;
    }

    rehash();
  }

  std::list<std::pair<Key, Value>> *buckets;
  size_t m_bucket_count{0};
  size_t num_elements{0};
  float max_load_factor;
};

void test_hash_map() {
  hash_map<int, int> map(1.0, 1);

  map.insert(1, 1);
  std::cout << "Size: " << map.size() << std::endl;
  map.insert(2, 1);
  std::cout << "Size: " << map.size() << std::endl;
  map.erase(1);
  std::cout << "Size: " << map.size() << std::endl;

  map.display();
  for (int i = 0; i < 20; i++) {
    map.insert(i, 1);
  }
  map.display();
}

int main() {
  test_hash_map();
  return EXIT_SUCCESS;
}