// ��� �����-������������. (-:
var ie = document.all && document.all.item && !window.opera;
if ( !ie ) {
	var el_in_find_td = document.getElementById('in_find_td');
	el_in_find_td.style.borderTop = "2px groove ButtonFace";
}

// ��������� ��������� �����, ���� ��� ����������.
function dnsearchChangeMode() {
	if ( document.forms['dnsearch_form']['mode'].value == "regex" ) {
		document.forms['dnsearch_form']['logic'].disabled = true;
	} else {
		document.forms['dnsearch_form']['logic'].disabled = false;
	}
}

// �������� �� ����������� ������� ��������� ������.
function openLocalFile(file, blank) {
	if ( file.match( /^file:/ ) ) {
		try {
			if ( !blank ) { document.location = file; }
			else          { window.open(file);        }
		} catch (e) {
			alert('��� ������� �� ����� ������� �� ��������� ������. ������ ����� ��� ������� � ����������� ������������ ������ ����������������� ������. ���� �� ����������� ������� Mozilla (� ������ �������� ������� ����� Firefox), ��� ���������� ������ � �������� ������ �about:config�, ����� ����� ����� �security.checkloaduri� � ��������� � �������� ��� �false�. ����� ���� �������� �� ������� ���������� �� ��������� �������. ���� �� �� ����������� ������ �������, �������� ��� ��������� ������������.\n\n����� ����, ������������� ������ ���������� ��������� � ��������� ������� ���������� �Kaspersky Anti-Hacker�.\n\n���, ��� ����� ��� ������� ��� ������� �������� �� ��������� ������:\n'+e);
		}
		return false;
	} else { return true; }
}
