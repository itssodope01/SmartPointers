
#include <SmartPointers/ProducerConsumer.h>

namespace smartPointers
{
    ProducerConsumer::ProducerConsumer(int numProducedItems, std::chrono::milliseconds productionDelay,
                                   std::chrono::milliseconds consumerADelay, std::chrono::milliseconds consumerBDelay)
  : numProducedItems_(numProducedItems),
    productionDelay_(productionDelay),
    consumerADelay_(consumerADelay),
    consumerBDelay_(consumerBDelay),
    queue_(), queue_mutex_(), cout_mutex_(), productionFinished_(false) {}

void ProducerConsumer::start() {
  std::thread producerThread(&ProducerConsumer::producer, this);
  std::thread consumerAThread(&ProducerConsumer::consumer, this, "A", consumerADelay_);
  std::thread consumerBThread(&ProducerConsumer::consumer, this, "B", consumerBDelay_);

  producerThread.join();
  consumerAThread.join();
  consumerBThread.join();
}

void ProducerConsumer::producer() {
  for (int i = 0; i < numProducedItems_; i++) {
    std::this_thread::sleep_for(productionDelay_);
    std::lock_guard<std::mutex> lock(queue_mutex_);
    std::lock_guard<std::mutex> cout_lock(cout_mutex_);
    std::cout << "Produced " << i << "\n";
    queue_.push(i);
  }
  productionFinished_ = true;
}

void ProducerConsumer::consumer(std::string type, const std::chrono::milliseconds delay) {
  while (true) {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    if (!queue_.empty()) {
      int item = queue_.front();
      queue_.pop();
      lock.unlock();
      std::this_thread::sleep_for(delay);
      std::lock_guard<std::mutex> cout_lock(cout_mutex_);
      std::cout << "Consumer " << type << " consumed " << item << "\n";
    } else if (productionFinished_) {
      break;
    }
  }
}
}  // namespace smartPointers
