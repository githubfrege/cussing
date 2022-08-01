using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.IO;
using System.Text.RegularExpressions;
using System.Diagnostics;



namespace Cussing
{
    public partial class CussChecker : Form
    {
        public WebClient client = new WebClient();
        public static string dictionaryPath = "pg13.txt";
        public List<string> safeWords = new List<string>() { "TITLE", "DOCUMENT", "SPACE" };
        public static List<string> cussWordList = new List<String>(File.ReadAllLines(dictionaryPath, Encoding.UTF8));
        public CussChecker()
        {
            InitializeComponent();

        }
        public static string StripHTML(string input)
        {
            return Regex.Replace(input, "<.*?>", String.Empty);
        }


        private void btnCheck_Click(object sender, EventArgs e)
        {
            listBox.DataSource = null;
            Uri myUri = new Uri(urlBox.Text, UriKind.Absolute);
            string downloadedString = StripHTML(client.DownloadString(myUri)).ToUpper();
            List<string> cussWordsOnSite = new List<string>();
            foreach (string safeWord in safeWords)
            {
                downloadedString = downloadedString.Replace(safeWord, String.Empty);
            }
            foreach (string cussWord in cussWordList)
            {
                if (downloadedString.Contains(cussWord.ToUpper()))
                {
                    cussWordsOnSite.Add(cussWord);
                }
            }
            listBox.DataSource = cussWordsOnSite;
         }
    }
}
