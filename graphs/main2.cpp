#include "graphs.hpp"
#include<iostream>
#include<string>
using namespace std;
using namespace colors;
int main(){

    UndirectedGraph<string> mysocialnetwork;

    
    mysocialnetwork.addEdge("Robin", "Rouvald");
    mysocialnetwork.addEdge("Zora", "Rouvald");
    mysocialnetwork.addEdge("Alexander", "Zora");
    // Cycle 1: Alexander-Zora-Rouvald-Robin-Alexander
    mysocialnetwork.addEdge("Alexander", "Robin");
    // Cycle 2: A small triangle involving Zora, Robin, and a new friend, Sarah
    mysocialnetwork.addEdge("Sarah", "Zora");
    mysocialnetwork.addEdge("Sarah", "Robin");
    mysocialnetwork.addEdge("Sarah", "Rouvald");
    
    // Cycle 3: Marcus, Leo, Alexander, and Zora
    mysocialnetwork.addEdge("Marcus", "Rouvald");
    mysocialnetwork.addEdge("Leo", "Marcus");
    mysocialnetwork.addEdge("Leo", "Alexander");
    mysocialnetwork.addEdge("Zora", "Marcus"); // This completes Cycle 3: Marcus-Zora-Alexander-Leo-Marcus
    
    // Cycle 4: A triangle involving Ethan, Nina, and Rouvald
    mysocialnetwork.addEdge("Ethan", "Nina"); // New Nodes: Ethan, Nina
    mysocialnetwork.addEdge("Ethan", "Rouvald");
    mysocialnetwork.addEdge("Nina", "Rouvald"); // This completes Cycle 4: Ethan-Nina-Rouvald-Ethan
    
    mysocialnetwork.display(true);
                                                 
    cout << "No of people (vertices) = " << mysocialnetwork.getNumVertices()  << endl << endl;
    cout << "Total Relationships (edges) = " << mysocialnetwork.getNumEdges()  << endl << endl;

    cout << "Below are the people in this group: "  << endl << endl;
    for (const string& person : mysocialnetwork.getVertices()){
        cout << person << "\n";
    }

    cout << "Degree of the vertex (No of relationships a person has): "  << endl << endl;
    cout << "Minimum no of relationships = " << mysocialnetwork.getMinDegree()  << endl << endl;
    cout << "Maximum no of relationships = " << mysocialnetwork.getMaxDegree()  << endl << endl;

    cout << "Distance between 2 vertices (How many relations does 2 people have between them) Robin & Zora: "<< mysocialnetwork.getDistance("Robin", "Zora") << endl << endl;

    cout << "Radius of the Graph (minimum eccentricity of any vertex) " << mysocialnetwork.getRadius() << endl << endl;

    cout << "Diameter of the Graph (maximum eccentricity of any vertex) " << mysocialnetwork.getDiameter() << endl << endl;

    cout << "Girth of a Graph (Length of the shortest cycle in a graph): " << mysocialnetwork.getGirth() << endl << endl;

    cout << "Circumference of the Graph (Length of the longest cycle in a graph) " << mysocialnetwork.getCircumference() << endl << endl;

    cout << BOLD << orange << "Testing Null Graph" << RESET << endl;
    NullGraph<char> ng;
    ng.addVertex('A');
    ng.addVertex('B');
    ng.display(true);

    return 0;
}
