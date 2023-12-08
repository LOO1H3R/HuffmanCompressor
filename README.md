# HuffmanCompressor
Data Structures Final Project

Authors: Alejandro D'haria, Eduardo Castellanos (@LaloCapacha3) and Luther Williams (@LOO1H3R)

## Description

This is the final project for the Data Structures Class. Programmed in C, this program uses the Huffman Coding Algorithm to reduce the size of a simple text paragraph.

### How it works

First of all, the program receives an array of characters, after that, it counts the frequency of each character and uses an ADT of a priority queue to manage it. When the priority queue is completed, the program starts building a Huffman Tree (see the image below) getting the character with the smallest frequency and pairing it with the second's smallest character, each pairing gets the sum of the two frequencies and it's returned to the priority queue.

![512px-Huffman_tree_2 svg](https://github.com/LOO1H3R/HuffmanCompressor/assets/77658990/da11ce78-c7d7-4b79-88b2-beec2d6c5e1f)
_Meteficha, Public domain, via Wikimedia Commons_


Once the tree is built, we use a HashMap to associate the binary code that we get after traversal the tree, whit each code we just replace the character to compress the text, if we want to decompress we need to make a new traversal to find the character.
