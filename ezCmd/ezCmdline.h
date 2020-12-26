/******************************************************************************
*
*  file:  eeZCmdline.h
*
*  Copyright (c) 2015, Yi Zhong. *
*  All rights reserved.
*
*  See the file COPYING in the top directory of this distribution for
*  more information.
*
*  THE SOFTWARE IS PROVIDED _AS IS_, WITHOUT WARRANTY OF ANY KIND, EXPRESS
*  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
*  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
*  DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/

#ifndef _EZCOMMANDLINE
#define _EZCOMMANDLINE

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <memory>

using namespace std;


class eZParam {

public:
	typedef enum { INT_OPT, FLOAT_OPT, DOUBLE_OPT, STRING_OPT, CUSTORM_OPT } OptValueType;
	eZParam(const string& strOpt,
		const string& strOptFullname,
		const string& strDesc,
		bool bReq,
		OptValueType valuetype);
	
	eZParam(const string& strOpt,
		const string& strOptFullname,
		const string& strDesc);

	virtual ~eZParam() {};
	void setOptValue(string strValue);
	bool isReq();

	bool		isMatch(string strArg);
	string getDesc();
	string getOptionFullname();
	string getOpt();
	string getOptStringvalue();
	OptValueType m_valuetype;

	void getValue(int& value);
	void getValue(float& value);
	void getValue(double& value);
	void getValue(string& value);

protected:
	string m_strDesc;
	string m_strOpt;
	string m_strOptFullname;
	string m_strOptValue;
	bool m_bReq;
};


eZParam::eZParam(const string& strOpt,
	const string& strOptFullname,
	const string& strDesc,
	bool bReq,
	OptValueType valuetype) {

	m_strOpt = strOpt;
	m_strOptFullname = strOptFullname;
	m_strDesc = strDesc;
	m_bReq = bReq;
	m_valuetype = valuetype;

}

eZParam::eZParam(const string& strOpt,
	const string& strOptFullname,
	const string& strDesc) {

	m_strOpt = strOpt;
	m_strOptFullname = strOptFullname;
	m_strDesc = strDesc;
	m_bReq = false;

}


bool eZParam::isMatch(string strArg)
{
	string str = strArg;
	//transform(str.begin(),str.end(),::tolower());
	if (str.compare(m_strOpt) == 0 || str.compare(m_strOptFullname) == 0) {
		return true;
	}

	return false;
}

bool eZParam::isReq() {
	return m_bReq;
}

void eZParam::setOptValue(string strValue) {
	m_strOptValue = strValue;
}

string eZParam::getDesc() {
	return m_strDesc;
}
string eZParam::getOptionFullname() {
	return m_strOptFullname;
}
string eZParam::getOpt() {
	return m_strOpt;
}

string eZParam::getOptStringvalue() {
	return m_strOptValue;

}

void	eZParam::getValue(int& value) {
	value = atoi(m_strOptValue.c_str());
}

void	eZParam::getValue(float& value) {
	value = (float)atof(m_strOptValue.c_str());
}

void	eZParam::getValue(double& value) {
	value = atof(m_strOptValue.c_str());
}

void	eZParam::getValue(string& value) {
	value = m_strOptValue;
}

//////////////////////////////////////////////////////////////////////////
class eZCmdline {

public:
	eZCmdline(const string& strDes);
	virtual ~eZCmdline(void);

	void setDescription(const string& strDes);
	//void init();
	//int parse(const string strcmdline);
	int parse(int argc, char** argv);

	int addOption(eZParam& valopt);
	int showOptions();

	//int getOption(eZParam valopt);

protected:
	eZParam* whichOption(string strArg);
	string m_strVer;
	string m_strDesc;
	string m_strProgname;

private:

	list<eZParam*> m_listOpts;
};

eZCmdline::eZCmdline(const string& strDes) {
	m_strDesc = strDes;
#if _DEBUG
	cout << m_strDesc << endl;
#endif

}

eZCmdline::~eZCmdline() {

}

void eZCmdline::setDescription(const string& strDes) {

	m_strDesc = strDes;
}

int eZCmdline::parse(int argc, char** argv) {

	vector<string> args;
	for (int i = 0; i < argc; i++) {
		args.push_back(argv[i]);
	}

	m_strProgname = args.front();
	args.erase(args.begin());

	for (int i = 0; i < args.size(); ) {
		eZParam* pt = whichOption(args[i]);
		if (pt != NULL && pt->isReq()) {
			i++;
			if (i == argc - 1) {
				break;
			}

			string strOptValue;
			int first = i;
			while (whichOption(args[i]) == NULL) {
				if (i > first) {
					strOptValue += " ";
				}

				strOptValue += args[i];
				i++;
				if (i == argc - 1) {
					break;
				}
			}
			pt->setOptValue(strOptValue);
			i--;
		}
		i++;
	}

	return 0;
}

int eZCmdline::addOption(eZParam& valopt) {

	m_listOpts.push_back(&valopt);
	return 0;
}

eZParam* eZCmdline::whichOption(string strArg)
{
	list<eZParam*>::iterator it;

	for (it = m_listOpts.begin(); it != m_listOpts.end(); it++) {
		if ((*it)->isMatch(strArg)) {
			return *it;
		}
	}

	return NULL;
}

int eZCmdline::showOptions()
{
	list<eZParam*>::iterator it;
	cout << m_strDesc << endl;

	for (it = m_listOpts.begin(); it != m_listOpts.end(); it++) {
		cout << (*it)->getDesc() << endl;
		cout << (*it)->getOptionFullname() << endl;
		cout << (*it)->getOptStringvalue() << endl;
	}

	return 0;
}
#endif