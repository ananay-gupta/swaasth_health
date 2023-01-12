import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'dart:convert';

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
  // Declare variables to store the form data
  bool _question1 = false;
  bool _question2 = false;
  bool _question3 = false;
  bool _question4 = false;
  bool _question5 = false;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text("VIRTUAL DOCTOR"),
        centerTitle: true,
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Form(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              // Question 1
              Text("Medication"),
              SwitchListTile(
                value: _question1,
                onChanged: (value) {
                  setState(() {
                    _question1 = value;
                  });
                },
                title: Text(_question1 ? "Yes" : "No"),
              ),
              // Question 2
              Text("Acidious"),
              SwitchListTile(
                value: _question2,
                onChanged: (value) {
                  setState(() {
                    _question2 = value;
                  });
                },
                title: Text(_question2 ? "Yes" : "No"),
              ),
              // Question 3
              Text("Cold"),
              SwitchListTile(
                value: _question3,
                onChanged: (value) {
                  setState(() {
                    _question3 = value;
                  });
                },
                title: Text(_question3 ? "Yes" : "No"),
              ),
              // Question 4
              Text("Cough"),
              SwitchListTile(
                value: _question4,
                onChanged: (value) {
                  setState(() {
                    _question4 = value;
                  });
                },
                title: Text(_question4 ? "Yes" : "No"),
              ),
              // Submit button
              ElevatedButton(
                onPressed: () async {
                  var body = {
                    'question1': _question1,
                    'question2': _question2,
                    'question3': _question3,
                    'question4': _question4,
                    'question5': _question5,
                  };

                  // Send the POST request to the API
                  var response = await http.post(
                    Uri.parse(
                        'https://blr1.blynk.cloud/external/api/get?token=4NFZzThvWfDpS65W2AQ3XXczD-kTYa0K&v3&v6&v6&v10&v5'),
                    body: json.encode(body),
                    headers: {'Content-Type': 'application/json'},
                  );

                  // Process the response
                  if (response.statusCode == 200) {
                    print('Success!');
                  } else {
                    print('Error!');
                  } // Validate and submit the form
                },
                child: Text("Predict"),
              ),
              Text(
                  '\n The Person Is HEALTHY \n Pulse = 70 Temperature = 37 \n SPO2 = 98 \n \n \n'),
              Text(' \n \n \n Designed with ♡ by Team TechQuilla © 2023')
            ],
          ),
        ),
      ),
    );
  }
}
