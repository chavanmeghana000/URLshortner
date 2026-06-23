# URL Shortener (C++)

A console-based URL Shortener built in C++ that allows users to generate short URLs, create custom aliases, set expiry times, track clicks, and store data persistently using file handling.

## Features

* Generate random 6-character short URLs
* Create custom aliases for URLs
* Prevent duplicate URL creation
* Set optional expiry time for links
* Automatically remove expired URLs
* Retrieve original URL using short code
* Track number of clicks for each short URL
* Show analytics for all stored URLs
* Display the most clicked short URL
* Delete URLs manually
* Persistent storage using file handling (`urls.txt`)

## Technologies Used

* C++
* STL (`unordered_map`, `vector`)
* File Handling (`ifstream`, `ofstream`)
* Time handling (`time_t`, `ctime`)

## Data Structures Used

* `unordered_map<string,string>` for short → original URL mapping
* `unordered_map<string,string>` for original → short URL mapping
* `unordered_map<string,int>` for click tracking
* `unordered_map<string,time_t>` for expiry handling

## How It Works

1. User enters a long URL.
2. System generates a unique short code or accepts a custom alias.
3. URL mappings are stored in memory and saved to a file.
4. User can retrieve original URLs using short codes.
5. Expired links are automatically cleaned up.
6. Click counts are updated whenever a short URL is accessed.

## Menu Options

1. Shorten URL
2. Get Original URL
3. Show Analytics
4. Delete URL
5. Top Clicked URL
6. Exit

## Sample Run

Enter URL: google.com
Want custom alias? (y/n): n
Enter expiry time in seconds (0 for no expiry): 0

Short URL: abc123

Enter short code: abc123
Original URL: google.com

## Future Improvements

* Better random generation using `mt19937`
* Support for URL validation
* Add search by original URL
* Web-based frontend integration
* Database storage instead of text files

## Learning Outcomes

* Hash map based design
* File persistence
* Expiry handling using timestamps
* Data consistency across multiple maps
* CRUD operations implementation

## Author

Meghana

