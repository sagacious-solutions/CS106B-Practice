
// Question 09 - get cwd ------ THIS ONLY WORKS IN C++17+

//#include <iostream>
//#include <filesystem>

//int main() {
//    std::filesystem::path currentPath = std::filesystem::current_path();
//    std::cout << "Current working directory: " << currentPath << std::endl;
//    return 0;
//}

// Question 09 - get cwd C++14
//#include <iostream>
//#include <unistd.h>

//int main() {
//    char buffer[PATH_MAX];
//    getcwd(buffer, PATH_MAX);
//    std::cout << "Current working directory: " << buffer << std::endl;
//    return 0;
//}
