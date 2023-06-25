#include <stdio.h>
#include <stdlib.h>

#include "dns.h"

void magik(unsigned int param1, unsigned int param2);

void task3() {
    // TODO: call secret function with correct arguments
	magik(1, 69420);
}

void main() {
    struct dns_entry entries[] = {
        [0].ip = 2966034245,
        [0].hostname = "google.com",
        [1].ip = 2966034246,
        [1].hostname = "facebook.com",
        [2].ip = 2966034247,
        [2].hostname = "curs.upb.ro",
        [3].ip = 2966034248,
        [3].hostname = "ocw.cs.pub.ro",
        [4].ip = 2966034249,
        [4].hostname = "fep.grid.pub.ro",
        [5].ip = 2966034250,
        [5].hostname = "youtube.com",
    };

    int target_ip = 168886273; // 10.17.0.1

    task2(entries, 6, target_ip);
    task3();
}
