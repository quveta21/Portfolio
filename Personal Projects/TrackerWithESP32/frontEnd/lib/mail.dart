// import 'package:flutter/foundation.dart';
// import 'package:flutter/material.dart';
//
// import 'package:provider/provider.dart';
// import 'package:serious_attempt/service.dart';
//
// void main() {
//   runApp(const DeviceScreen());
// }
//
//
// class DeviceScreen extends StatefulWidget {
//   const DeviceScreen({super.key});
//   @override
//   _DeviceScreenState createState() => _DeviceScreenState();
// }
//
// class _DeviceScreenState extends State<DeviceScreen> {
//   final ToShowMess _bleService = ToShowMess();
//   final TextEditingController _messageController = TextEditingController();
//   String _receivedMessage = "";
//
//   @override
//   void initState() {
//     super.initState();
//     _connectToDevice();
//   }
//
//
//
//   Future<void> _connectToDevice() async {
//     await _bleService.scanDevices(const Duration(seconds: 10));
//     await _bleService.connectToDevice("TrackerESP32");
//   }
//
//   @override
//   void dispose() {
//     _bleService.disconnect();
//     _messageController.dispose();
//     super.dispose();
//   }
//
//   @override
//   Widget build(BuildContext context) {
//     return
//       MaterialApp(
//       home:Scaffold(
//       appBar: AppBar(title: Text("ESP32 BLE Communication")),
//       body: Padding(
//         padding: const EdgeInsets.all(16.0),
//         child: Column(
//           children: [
//             TextField(
//               controller: _messageController,
//               decoration: InputDecoration(
//                 labelText: "Message to ESP32",
//                 border: OutlineInputBorder(),
//               ),
//             ),
//             SizedBox(height: 20),
//             ElevatedButton(
//               onPressed: () async {
//
//                 if (_messageController.text.isNotEmpty) {
//                   compute(_bleService.sendMessage, _messageController.text);
//
//                   _messageController.clear();
//                 }
//               },
//               child: Text("Send Message"),
//             ),
//             SizedBox(height: 20),
//             Text(
//               "Received Messages:",
//               style: TextStyle(fontSize: 18, fontWeight: FontWeight.bold),
//             ),
//             SizedBox(height: 10),
//             Text(_receivedMessage),
//           ],
//         ),
//       ),
//     ),
//       );
//   }
// }
//
//
//
// class MyApp extends StatelessWidget {
//   const MyApp({super.key});
//
//   @override
//   Widget build(BuildContext context) {
//     return MaterialApp(
//       title: 'Simple Button Demo',
//       theme: ThemeData(
//         primarySwatch: Colors.blue,
//       ),
//       home: const ButtonDemoPage(),
//     );
//   }
// }
//
// class ButtonDemoPage extends StatefulWidget {
//   const ButtonDemoPage({super.key});
//
//   @override
//   State<ButtonDemoPage> createState() => _ButtonDemoPageState();
// }
//
// class _ButtonDemoPageState extends State<ButtonDemoPage> {
//   String _buttonText = 'Click Me!';
//   int _clickCount = 0;
//
//   void _handleButtonPress() {
//     setState(() {
//       _clickCount++;
//       _buttonText = 'Pressed $_clickCount times';
//     });
//   }
//
//   @override
//   Widget build(BuildContext context) {
//     return Scaffold(
//       appBar: AppBar(
//         title: const Text('Button Demo'),
//       ),
//       body: Center(
//         child: Column(
//           mainAxisAlignment: MainAxisAlignment.center,
//           children: [
//             ElevatedButton(
//               onPressed: _handleButtonPress,
//               style: ElevatedButton.styleFrom(
//                 padding: const EdgeInsets.all(20),
//                 backgroundColor: Colors.blue,
//                 foregroundColor: Colors.white,
//               ),
//               child: Text(_buttonText),
//             ),
//             const SizedBox(height: 20),
//             Text(
//               'Button pressed $_clickCount times',
//               style: const TextStyle(fontSize: 18),
//             ),
//           ],
//         ),
//       ),
//     );
//   }
// }