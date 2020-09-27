# Debacle

An application for learning foreign words, 2019.

## Build instructions

__Requirements__: Qt Creator 4+

1. Download code
2. Open `debacle.pro` using Qt Creator
3. Configure project
4. Build

## What is it

This application can help you memorize foreign words.

In the start screen, you can choose which language are you learning at the moment (or add new one).

At the next screen you will see something like a dictionary where you can add new words or revise old ones.

There are 2 types of tests:
1. Whether you know the meaning of the word (`Run test`)
2. Whether you can guess the word by its meaning (`Run inverse test`)

## How is it working

The words for a test are chosen using your previous answers. This is why you will quite often get the words you don't know.

To be more specific, each word has a status. If you have answered `yes` to the question for the word, its status will increase by 1. If you have answered `no`, it will decrease by 1. And if you have clicked `I was wrong`, the status will decrease by two.

Then 20 words with the least statuses are chosen to the test. They will be asked in random order.
