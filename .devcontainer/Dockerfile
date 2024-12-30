# Używamy uniwersalnego obrazu deweloperskiego od Microsoft jako obrazu bazowego
FROM mcr.microsoft.com/devcontainers/universal:latest

# Kopiujemy skrypt konfiguracyjny do kontenera
COPY setup-bash.sh /usr/local/bin/

# Uruchamiamy skrypt konfiguracyjny i instalujemy wymagane pakiety
RUN chmod +x /usr/local/bin/setup-bash.sh && \
    /usr/local/bin/setup-bash.sh && \
    rm /usr/local/bin/setup-bash.sh && \
    # Aktualizacja listy pakietów
    apt-get update && \
    # Instalacja wymaganych narzędzi deweloperskich i zależności
    DEBIAN_FRONTEND=noninteractive apt-get install -y python3 python3-pip mingw-w64 g++ cmake make git gdb ghostscript doxygen graphviz && \
    # Czyszczenie w celu zmniejszenia rozmiaru obrazu
    apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/cache/apt/* /var/log/* /usr/share/doc/* /usr/share/man/* && \
    apt-get autoremove -y && \
    pip3 cache purge
