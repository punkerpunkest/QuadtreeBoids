#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <string>

class Profiler{
    public:
        static Profiler& get(){
            static Profiler instance;
            return instance;
        }
        void begin (const std::string& name){
            starts_[name] = std::chrono::high_resolution_clock::now();
        }
        void end (const std::string& name){
            auto now = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - starts_[name]).count();
            totals_[name] += duration;
            counts_[name]++;
        }
        void print(){
            std::cout << "\nTiming Results: \n";
            for (const auto& [name, total]: totals_){
                std::cout << name << ": " << total / counts_[name] << " us average (" << counts_[name] << " calls)\n";
            }
        }

    private:
        Profiler() = default;
        std::unordered_map<std::string, std::chrono::high_resolution_clock::time_point> starts_;
        std::unordered_map<std::string, long long> totals_;
        std::unordered_map<std::string, int> counts_;
};

class ScopedTimer{
    public:
        ScopedTimer(const std::string& name): name_(name){
            Profiler::get().begin(name_);
        }
        ~ScopedTimer() {
            Profiler::get().end(name_);
        }
    private:
        std::string name_;
};

#define PROFILE(name) ScopedTimer timer_##__LINE__(name) 