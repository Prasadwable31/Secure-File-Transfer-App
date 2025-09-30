using System;
using System.Drawing;
using System.IO;
using System.Windows.Forms;

namespace Crypto_UI
{
    public partial class Form1 : Form
    {
        // DLL Imports
        [System.Runtime.InteropServices.DllImport("EncryptDecrypt.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public static extern void Encrypt_Caesar_Cipher(string src, string dest, int key);
        [System.Runtime.InteropServices.DllImport("EncryptDecrypt.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public static extern void Decrypt_Caesar_Cipher(string src, string dest, int key);
        [System.Runtime.InteropServices.DllImport("EncryptDecrypt.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public static extern void Encrypt_XOR_Cipher(string src, string dest, char key);
        [System.Runtime.InteropServices.DllImport("EncryptDecrypt.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public static extern void Decrypt_XOR_Cipher(string src, string dest, char key);
        [System.Runtime.InteropServices.DllImport("EncryptDecrypt.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public static extern void Encrypt_Vigenere_Cipher(string src, string dest, string key);
        [System.Runtime.InteropServices.DllImport("EncryptDecrypt.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public static extern void Decrypt_Vigenere_Cipher(string src, string dest, string key);
        [System.Runtime.InteropServices.DllImport("EncryptDecrypt.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public static extern void Encrypt_Vigenere_XOR_Cipher(string src, string dest, string key);
        [System.Runtime.InteropServices.DllImport("EncryptDecrypt.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public static extern void Decrypt_Vigenere_XOR_Cipher(string src, string dest, string key);
        [System.Runtime.InteropServices.DllImport("EncryptDecrypt.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public static extern void Encrypt_Reverse_Cipher(string src, string dest);
        [System.Runtime.InteropServices.DllImport("EncryptDecrypt.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public static extern void Decrypt_Reverse_Cipher(string src, string dest);
        [System.Runtime.InteropServices.DllImport("EncryptDecrypt.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public static extern void Encrypt_Substitution_Cipher(string src, string dest);
        [System.Runtime.InteropServices.DllImport("EncryptDecrypt.dll", CallingConvention = System.Runtime.InteropServices.CallingConvention.Cdecl)]
        public static extern void Decrypt_Substitution_Cipher(string src, string dest);

        // Controls
        private TextBox txtSource, txtKey;
        private ComboBox cmbAlgo;
        private Label lblStatus;

        public Form1()
        {
            InitializeComponent();
            InitUI();
            cmbAlgo.SelectedIndexChanged += CmbAlgo_SelectedIndexChanged;
        }

        private void Form1_Load(object sender, EventArgs e) { }

        private void InitUI()
        {
            // Form settings
            this.Text = "Secure File Transfer App";
            this.BackColor = Color.FromArgb(44, 62, 80);
            this.Size = new Size(640, 450);
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;

            // Title Label
            Label title = new Label();
            title.Text = "🔐 Secure File Transfer App";
            title.Font = new Font("Segoe UI", 20, FontStyle.Bold);
            title.ForeColor = Color.White;
            title.AutoSize = true;
            title.Location = new Point(120, 20);
            this.Controls.Add(title);

            // Source File
            Label lblSource = new Label();
            lblSource.Text = "Source File:";
            lblSource.Font = new Font("Segoe UI", 12, FontStyle.Regular);
            lblSource.ForeColor = Color.White;
            lblSource.Location = new Point(60, 100);
            this.Controls.Add(lblSource);

            txtSource = new TextBox();
            txtSource.Text = "Select File...";
            txtSource.ForeColor = Color.Gray;
            txtSource.Size = new Size(300, 30);
            txtSource.Location = new Point(180, 100);

            // When user clicks (focus), clear placeholder
            txtSource.GotFocus += (s, e) =>
            {
                if (txtSource.Text == "Select File...")
                {
                    txtSource.Text = "";
                    txtSource.ForeColor = Color.Black;
                }
            };

            // When user leaves empty, restore placeholder
            txtSource.LostFocus += (s, e) =>
            {
                if (string.IsNullOrWhiteSpace(txtSource.Text))
                {
                    txtSource.Text = "Select File...";
                    txtSource.ForeColor = Color.Gray;
                }
            };
            this.Controls.Add(txtSource);

            // Browse Button
            Button btnBrowse = new Button();
            btnBrowse.Text = "📂 Browse";
            btnBrowse.BackColor = Color.FromArgb(52, 152, 219);
            btnBrowse.ForeColor = Color.White;
            btnBrowse.FlatStyle = FlatStyle.Flat;
            btnBrowse.Size = new Size(70, 25);
            btnBrowse.Location = new Point(490, 100);
            btnBrowse.Click += BtnBrowse_Click; // attach click event
            this.Controls.Add(btnBrowse);

            // Cipher Key
            Label lblKey = new Label();
            lblKey.Text = "Cipher Key:";
            lblKey.Font = new Font("Segoe UI", 12, FontStyle.Regular);
            lblKey.ForeColor = Color.White;
            lblKey.Location = new Point(60, 150);
            this.Controls.Add(lblKey);

            txtKey = new TextBox();
            txtKey.Size = new Size(300, 30);
            txtKey.Location = new Point(180, 150);

            // Start with placeholder
            txtKey.Text = "Enter Cipher Key...";
            txtKey.ForeColor = Color.Gray;
            txtKey.UseSystemPasswordChar = false;

            // Handle focus (when user clicks inside)
            txtKey.Enter += (s, e) =>
            {
                if (txtKey.Text == "Enter Cipher Key...")
                {
                    txtKey.Text = "";
                    txtKey.ForeColor = Color.Black;
                    txtKey.UseSystemPasswordChar = true; // mask only when user types
                }
            };

            // Handle focus lost (when user leaves textbox)
            txtKey.Leave += (s, e) =>
            {
                if (string.IsNullOrWhiteSpace(txtKey.Text))
                {
                    txtKey.Text = "Enter Cipher Key...";
                    txtKey.ForeColor = Color.Gray;
                    txtKey.UseSystemPasswordChar = false; // remove mask for placeholder
                }
            };
            this.Controls.Add(txtKey);

            // Algorithm Dropdown
            Label lblAlgo = new Label();
            lblAlgo.Text = "Algorithm:";
            lblAlgo.Font = new Font("Segoe UI", 12, FontStyle.Regular);
            lblAlgo.ForeColor = Color.White;
            lblAlgo.Location = new Point(60, 200);
            this.Controls.Add(lblAlgo);

            cmbAlgo = new ComboBox();
            cmbAlgo.Items.AddRange(new string[] { "Caesar Cipher", "XOR Cipher", "Vigenère Cipher" , "Vigenere XOR" , "Reverse Cipher" , "Substitution Cipher" });
            cmbAlgo.Size = new Size(300, 30);
            cmbAlgo.Location = new Point(180, 200);
            cmbAlgo.DropDownStyle = ComboBoxStyle.DropDownList;
            this.Controls.Add(cmbAlgo);

            // Encrypt Button
            Button btnEncrypt = new Button();
            btnEncrypt.Text = "🔒 Encrypt";
            btnEncrypt.BackColor = Color.FromArgb(46, 204, 113);
            btnEncrypt.ForeColor = Color.White;
            btnEncrypt.FlatStyle = FlatStyle.Flat;
            btnEncrypt.Size = new Size(120, 40);
            btnEncrypt.Location = new Point(180, 270);
            this.Controls.Add(btnEncrypt);

            // Decrypt Button
            Button btnDecrypt = new Button();
            btnDecrypt.Text = "🔓 Decrypt";
            btnDecrypt.BackColor = Color.FromArgb(231, 76, 60);
            btnDecrypt.ForeColor = Color.White;
            btnDecrypt.FlatStyle = FlatStyle.Flat;
            btnDecrypt.Size = new Size(120, 40);
            btnDecrypt.Location = new Point(320, 270);
            this.Controls.Add(btnDecrypt);

            btnEncrypt.Click += (s, e) => RunCrypto(true);   // true = encrypt
            btnDecrypt.Click += (s, e) => RunCrypto(false);  // false = decrypt

            // Status Label
            lblStatus = new Label();
            lblStatus.Text = "Status: Waiting...";
            lblStatus.Font = new Font("Segoe UI", 10, FontStyle.Italic);
            lblStatus.ForeColor = Color.LightGray;
            lblStatus.AutoSize = true;
            lblStatus.Location = new Point(180, 345);
            this.Controls.Add(lblStatus);
        }

        private void RunCrypto(bool isEncrypt)
        {
            string src = txtSource.Text;
            //string dest = isEncrypt ? "enc.txt" : "dec.txt";
            string dest = isEncrypt
            ? Path.Combine(Path.GetDirectoryName(src), "enc.txt")
            : Path.Combine(Path.GetDirectoryName(src), "dec.txt");

            string algo = cmbAlgo.SelectedItem.ToString();
            string key = txtKey.Text;

            try
            {
                switch (algo)
                {
                    case "Caesar Cipher":
                        int caesarKey = int.Parse(key);
                        if (isEncrypt) Encrypt_Caesar_Cipher(src, dest, caesarKey);
                        else Decrypt_Caesar_Cipher(src, dest, caesarKey);
                        break;

                    case "XOR Cipher":
                        char xorKey = key[0];
                        if (isEncrypt) Encrypt_XOR_Cipher(src, dest, xorKey);
                        else Decrypt_XOR_Cipher(src, dest, xorKey);
                        break;

                    case "Vigenère Cipher":
                        if (isEncrypt) Encrypt_Vigenere_Cipher(src, dest, key);
                        else Decrypt_Vigenere_Cipher(src, dest, key);
                        break;

                    case "Vigenere XOR":
                        if (isEncrypt) Encrypt_Vigenere_XOR_Cipher(src, dest, key);
                        else Decrypt_Vigenere_XOR_Cipher(src, dest, key);
                        break;

                    case "Reverse Cipher":
                        if (isEncrypt) Encrypt_Reverse_Cipher(src, dest);
                        else Decrypt_Reverse_Cipher(src, dest);
                        break;

                    case "Substitution Cipher":
                        if (isEncrypt) Encrypt_Substitution_Cipher(src, dest);
                        else Decrypt_Substitution_Cipher(src, dest);
                        break;
                }

                lblStatus.Text = $"✅ {algo} {(isEncrypt ? "Encryption" : "Decryption")} Done!";
                lblStatus.ForeColor = Color.LightGreen;
            }
            catch (Exception ex)
            {
                lblStatus.Text = $"❌ Error: {ex.Message}";
                lblStatus.ForeColor = Color.Red;
            }
        }

        private void BtnBrowse_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog ofd = new OpenFileDialog())
            {
                ofd.Title = "Select Source File";
                ofd.Filter = "All Files (*.*)|*.*";

                if (ofd.ShowDialog() == DialogResult.OK)
                {
                    txtSource.Text = ofd.FileName;
                    txtSource.ForeColor = Color.Black;
                }
            }
        }

        private void CmbAlgo_SelectedIndexChanged(object sender, EventArgs e)
        {
            string algo = cmbAlgo.SelectedItem.ToString();

            // Disable key for algorithms that don't need it
            if (algo == "Reverse Cipher" || algo == "Substitution Cipher")
            {
                txtKey.Enabled = false;
                txtKey.Text = "Not Required";
                txtKey.ForeColor = Color.Gray;
            }
            else
            {
                txtKey.Enabled = true;
                txtKey.Text = "Enter Cipher Key...";
                txtKey.ForeColor = Color.Gray;
                txtKey.UseSystemPasswordChar = false;
            }
        }
    }
}
