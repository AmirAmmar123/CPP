Project README

This project focuses on Global Supply Chains and is developed by Amir Ammar from the computer science faculty of Tel-Hai. The project involves several classes and functionalities to handle supply chain operations.
Classes

    Graph
        Responsible for managing a graph data structure.
        Provides methods to add edges, retrieve vertices, and perform depth-first search.

    Factory
        Manages the creation and initialization of graph objects.
        Contains unique pointers to Graph objects for time and containers.
        Handles file operations and maintains a set of all files.
        Implements methods for loading files, performing outbound and inbound operations, and conducting depth-first search.

    Validator
        Contains various exception classes for handling validation errors.
        Exceptions include PortCityNameError, DateTimeError, InvalidLegalWeight, InvalidFileInput, InvalidInput, OpeningReadingError, NullPtr, InvalidNumberOfArgs, ARGVformatError, FileFailedToOpen, and CommandNotFound.
        Provides methods for validating names, weights, date and time formats, and command inputs.

    Chrono
        Represents a custom time duration.
        Converts a given date and time string into a time point using std::chrono library.

    CommandLine
        Implements a command-line interface for interacting with the program.
        Utilizes the Singleton design pattern to ensure a single instance of the class.
        Manages the GraphLoader object and listens for user input from the command line.

    GraphLoader
        Handles the loading and processing of graph data from files.
        Uses the Factory class to create and manipulate graph objects.
        Parses files, tokenizes input, and performs various graph operations.

    TokenIterator
        A custom iterator that tokenizes input based on specified delimiters.
        Implements functionality for iterating over a range of characters and extracting tokens.


Credits

Special credit goes to Dr. Ofir Shier for his implementation of the TokenIterator class, which is used in this project.

If you have any questions or issues, please contact Amir Ammar at amir.ammar.work@gmail.com