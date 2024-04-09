cmake_minimum_required(VERSION 3.20)
project(_DVC_Food_Pantry)

set(CMAKE_CXX_STANDARD 11)

add_executable(_DVC_Food_Pantry DVCFoodPantry.cpp PackageTracking.cpp Inventory.cpp Delivery.cpp)
