import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: HomePage(),
    );
  }
}

class HomePage extends StatefulWidget {
  @override
  _HomePageState createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  // Declare a variable to store the API response
  String _apiResponse = "";

  // Method to make the HTTP request and store the response
  _makeRequest() async {
    // Make the HTTP request
    const String apiEndPoint = 'https://catfact.ninja/fact';
    var response = await http.get(Uri.parse(apiEndPoint));

    // Store the response in the variable
    setState(() {
      _apiResponse = response.body;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("VIRTUAL DOCTOR"),
        centerTitle: true,
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            // Display a button to make the HTTP request
            ElevatedButton(
              onPressed: _makeRequest,
              child: Text("Predict"),
            ),
            // Display the API response
            Text(_apiResponse),
          ],
        ),
      ),
    );
  }
}
