#pragma once
#include <random>
#include <chrono>
#include <iostream>

#include <time.h> 

void ProvideSeed(std::mt19937& engine, int id) {
	std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::cout << "time " << t << std::endl;

	unsigned seed = unsigned(t);
	seed = (seed + id) << 3 - seed;

	engine.seed(seed);
}

int GetRandomNumber(std::mt19937& engine, int from, int to, int id) {
	std::uniform_int_distribution<size_t> distribution(from, to - 1);
	return distribution(engine);
}