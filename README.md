# Data Transfer Microcontroller

## EEE3097S Group Project

Welcome to the Data Transfer Microcontroller project repository. This repository contains all the necessary code and resources for our EEE3097S group project.

### Repository Structure

- **Code**: Contains the primary code used in the project.
- **Encryption**: Includes files related to data encryption.
- **Compression**: Contains files related to data compression.
- **Testing and Analysis Scripts**: Scripts written for testing and analysis purposes, including file similarity checks and FFT comparisons of input and output files.

### Additional Resources

- **Demonstration Video**: A video demonstration of the project.
- **Test Results**: Screenshots and results from various tests conducted during the design process.

### Usage Instructions

The following commands can be used in a Linux terminal or WSL terminal to run the compression and encryption processing blocks:

#### Whole Process

```bash
bzip2 -vk readSensorData.csv && \
openssl enc -aes-256-cbc -pbkdf2 -in readSensorData.csv.bz2 -out readSensorDataout.txt.bz2 -pass pass:ethan && \
rm readSensorData.csv.bz2 && \
openssl enc -d -aes-256-cbc -pbkdf2 -in readSensorDataout.txt.bz2 -out readSensorData.txt.bz2 -pass pass:ethan && \
bzip2 -d readSensorData.txt.bz2 && \
rm readSensorDataout.txt.bz2
```

#### Compression Only

```bash
bzip2 -vk readSensorData.csv
```

#### Encryption Only

```bash
openssl enc -aes-256-cbc -pbkdf2 -in readSensorData.csv.bz2 -out readSensorDataout.txt.bz2 -pass pass:ethan
```

#### Decryption Only

```bash
openssl enc -d -aes-256-cbc -pbkdf2 -in readSensorDataout.txt.bz2 -out readSensorData.txt.bz2 -pass pass:ethan
```

#### Decompression Only

```bash
bzip2 -d readSensorData.txt.bz2
```

We hope you find these resources helpful and effective.

Ethan Morris and Ethan Meknassi