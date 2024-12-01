#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <filesystem>
#include <stdexcept>
#include <atomic>

namespace fs = std::filesystem;

// Global sum and mutex for synchronization
std::atomic<long long> global_sum(0);
std::mutex log_mutex;

// Function to log messages
void log_message(const std::string& message) {
    std::lock_guard<std::mutex> lock(log_mutex);
    std::cerr << message << "\n";
}

// Function to process files and calculate the sum of integers
void process_files(const std::vector<std::string>& files) {
    try {
        long long local_sum = 0;
        for (const auto& file : files) {
            std::ifstream infile(file);
            if (!infile) {
                log_message("Error: Cannot open file " + file);
                continue;
            }

            int num;
            while (infile >> num) {
                local_sum += num;
            }

            if (infile.bad()) {
                log_message("Error: Failed to read file " + file);
            }
        }

        // Safely update the global sum
        global_sum += local_sum;

    } catch (const std::exception& e) {
        log_message(std::string("Exception in thread: ") + e.what());
    }
}

int main() {
    try {
        // Directory containing text files having digits stored
        std::string dir_path = "text_files";

        if (!fs::exists(dir_path)) {
            throw std::runtime_error("Directory does not exist: " + dir_path);
        }

        // Collect all text file paths
        std::vector<std::string> files;
        for (const auto& entry : fs::directory_iterator(dir_path)) {
            if (entry.path().extension() == ".txt") {
                files.push_back(entry.path().string());
            }
        }

        if (files.empty()) {
            throw std::runtime_error("No .txt files found in directory: " + dir_path);
        }

        // Split files among threads
        size_t num_threads = std::thread::hardware_concurrency();
        num_threads = num_threads > 0 ? num_threads : 4; // Fallback to 4 threads if hardware_concurrency fails

        std::vector<std::thread> threads;
        size_t chunk_size = (files.size() + num_threads - 1) / num_threads;

        for (size_t i = 0; i < num_threads; ++i) {
            size_t start = i * chunk_size;
            size_t end = std::min(start + chunk_size, files.size());
            if (start < end) {
                threads.emplace_back(process_files, std::vector<std::string>(files.begin() + start, files.begin() + end));
            }
        }

        // Join threads
        for (auto& thread : threads) {
            thread.join();
        }

        // Print the total sum
        std::cout << "Compilation successful and Total Sum: " << global_sum.load() << std::endl;

    } catch (const std::exception& e) {
        log_message(std::string("Fatal error: ") + e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}