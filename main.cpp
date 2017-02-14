#include "repovizz2_client.h"

int main() {
    // Create a repovizz2_client object
    repovizz2_client my_client(U("43e7a909-6011-47e2-b58e-200e72bd8b06"), U("33d728c7-a5ab-4406-86e6-9702c6546a5e"));

    // Authorize client
    my_client.authorize();

    // Try out some requests
    my_client.get(U("/api/v1.0/user"));
    my_client.post(U(""));

    return 0;
}



