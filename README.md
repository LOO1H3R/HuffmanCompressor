# HuffmanCompressor
Data Structures Final Project

Authors: Alejandro D'haria, Eduardo Castellanos (@LaloCapacha3), Luther Williams (@LOO1H3R)

## Description

This is the final project for the Data Structures Class. Programmed in C, this program uses the Huffman Coding Algorithm to reduce the size of a simple text paragraph.

### How it works

First of all, the program receives an array of characters, after that, it counts the frequency of each character and uses an ADT of a priority queue to manage it. When the priority queue is completed, the program starts building a Huffman Tree (see the image below) getting the character with the smallest frequency and pairing it with the second's smallest character, each pairing gets the sum of the two frequencies and its returned to the priority queue.
