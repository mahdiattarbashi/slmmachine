[![](http://dl.getdropbox.com/u/161208/Documents/WikiDocuments/slmLogo.png)](http://code.google.com/p/slmmachine/)
<br>
SMG LAN Messenger is an open source,cross platform, small, lightweight, instant messenger developed for in company use with encryption support. It is specifically designed for <b>low network</b> traffic. Since SMG LAN Messenger is based on <a href='http://en.wikipedia.org/wiki/Peer-to-peer'>P2P architecture</a>, there is no need to server. Clients can directly communicate each other. It is developed with <a href='http://doc.trolltech.com/4.5/index.html'>Qt4.5</a> using with the <a href='http://doc.trolltech.com/qtcreator-1.0/index.html'>Qt Creator 1.0.0 IDE.</a>

Main idea behind SLM is to achieve colleague communication with minimum network load. Similar LAN messengers are using <a href='http://en.wikipedia.org/wiki/User_Datagram_Protocol'>UDP</a> broadcasting to find online peers. This makes unnecessary network loads and IT guys do not like this condition especially in the secure company intranets. In SLM, buddy list is constructed manually by entering an alias and corresponding IP address or Host Name of the buddy. Also your peer should enter your alias and IP address or Host Name.<br>
<br>
SLM supports both message encryption and file encryption. Your messages are encrypting before network travel. By this way, your messages are protected from a third person which is also known as <a href='http://en.wikipedia.org/wiki/Man_in_the_middle_attack'>man in the middle</a>. This can be helpful to make private conservations between your colleagues.<br>
<br>
In future releases we will try to bring more and more features to SLM to make it a robust, reliable, useful messenger for company networks. You can reach our development plan at the <a href='TODOList.md'>TODO List</a> wiki page, any suggestions and comments are welcome.<br>
<br>
We have inspired from other open source projects when writing our code. We will update our site and code comments and give references to those codes. For now, our focus is to bring RC-release of SLM. Thank you for your attention and thank you for using SLM. Please do not forget that SLM is a hobby project developed between developers that want to contribute open source community.<br>
<br>
SUPPORT OPEN-SOURCE.<br>
<br>
<h3>News</h3>
<ul><li>SLM 1.0 Beta Version is out as promised on 15 March 2009 with lots of bug fixes.<br>
</li><li>SLM Beta version will be released on 15 March 2009.<br>
</li><li>Qt Creator 1.0.0 and Qt 4.5 is out. SLM is now being developed in QT 4.5 with Qt Creator 1.0.0.<br>
</li><li>Encrypted File transfer support is added, working fully functional. Feature will be included in beta release and can be reached any time from SVN(branch line)<br>
</li><li>SMG LAN Messenger pre-alfa version is released and can be reached from downloads section<br>
</li><li><a href='TODOList.md'>TODO List</a> is added on wiki pages<br>
</li><li>Any feature request can be added to the <a href='FeatureList.md'>feature list</a> wiki page as comment. We will consider these comments.</li></ul>

<h3>Available Features (Beta)</h3>
<ul><li>Basic contact list management<br>
</li><li>Basic encryption management<br>
</li><li>Encrypted messaging<br>
</li><li>Encrypted and Unencrypted File transfer</li></ul>

<h3>In-Progress Features (SVN):</h3>
<ul><li>Choosing different encryption strategies on-runtime