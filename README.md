# 🔐 Crypto UI – Secure File Transfer App  

## 📌 Technology  
- **UI Layer:** C# (.NET Framework, WinForms)
- **Core Logic:**  C/C++ (Win32 SDK, DLL)
- **Platform:** Windows 
---

## 📖 Project Overview  
A **Windows-based simulation project** that demonstrate the concept of **cryptography and system-level programming** by implementing multiple classical cryptographic algorithms using **UI** (C# WinForms) and **Win32 SDK**



This project showcases **low-level programming, system calls, DLL development and modern UI integration** in a pratical and secure context.

The DLL can be linked with any client application (C/C++, C#, Python with ctypes, etc.) to perform **file-based encryption and decryption**. 

---
## 📂 Project Structure

```
Crypto UI/
│
├─ bin/x64/Debug/EncryptDecrypt.dll         
├─ Form1.cs                    # Main UI logic
├─ Program.cs                  # Application entry point
└─ Crypto_UI.sln               # Visual Studio solution

  EncryptDecrypt.cpp          # encryption and decryption logic
  pch.cpp                     # pre compile header
  dllmain.cpp
  EncryptDecrypt.sln

```
---
## ⚡ Key Features

- **File-based Encryption & Decryption**
  - Supports secure encryption/decryption of text files.

- **Multiple Algorithms Implemented**
  - **Caesar Cipher** (character shift-based substitution)
  - **XOR Cipher** (bitwise XOR with user-defined key)
  - **Vigenere Cipher** 
  - **Reverse Cipher** (custom cipher)
  - **Substitution Cipher** (Custom mapping with a substitution key)

- **System-Level File Handling**
  - Uses **Win32 SDK APIs** (`CreateFile`, `ReadFile`, `WriteFile`, `CloseHandle`) instead of high-level C functions.

- **DLL Integration**
  - Exported reusable functions through a **custom DLL**.
  - Client applications dynamically load and use encryption/decryption services.

- **Low-Level Programming Practice**
  - Worked extensively with **pointers, buffers, and string processing**.
  - Strengthened debugging skills with **Visual Studio** and Windows tools.

---

## 🛠 Skills Highlighted  
- Low-level **file handling** with `_sopen_s`, `_read`, `_write`.  
- **Dynamic Link Library (DLL)** creation in Windows.  
- Knowledge of **cryptographic algorithms**.  
- Modular design with **exported functions** for external usage.  
- Implementation of **classical encryption & decryption techniques**  
- **Windows Forms UI design** with interactive controls.

---

## 📂 Example Usage  

![Crypto UI](<Image App.png>)

**Plaintext (Input.txt):**  
```
HELLO World! 123
```

**Caesar (Key = 3) → enc.txt:**  
```
KHOOR#Zruog$#456
```

**Decrypted → dec.txt:**  
```
HELLO World! 123
```

---

## 🚀 Future Enhancements  
- Add **Rail Fence Cipher** and **Playfair Cipher**.  
- Support **block ciphers (AES, DES)** for stronger encryption.  
- Provide a **command-line tool** linked with this DLL.  
- Add **error logging system** for debugging.  
