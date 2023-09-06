#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

namespace smartPointers
{
class ProducerConsumer {
public:
  ProducerConsumer(int numProducedItems, std::chrono::milliseconds productionDelay,
                   std::chrono::milliseconds consumerADelay, std::chrono::milliseconds consumerBDelay);
  void start();

private:
  void producer();
  void consumer(std::string type, const std::chrono::milliseconds delay);

  int numProducedItems_;
  std::chrono::milliseconds productionDelay_;
  std::chrono::milliseconds consumerADelay_;
  std::chrono::milliseconds consumerBDelay_;
  std::queue<int> queue_;
  std::mutex queue_mutex_;
  std::mutex cout_mutex_;
  bool productionFinished_ = false;
};
}  // namespace smartPointers
