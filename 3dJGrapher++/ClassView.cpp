
#include "stdafx.h"
#include "MainFrm.h"
#include "ClassView.h"
#include "Resource.h"
#include "3dJGrapher++.h"
#include "OpenGL.h"

IMPLEMENT_DYNCREATE(COpenGLView, CView);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


BEGIN_MESSAGE_MAP(COpenGLView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_COMMAND(ID_VIEW_QUAD, OnViewQuad)
	ON_UPDATE_COMMAND_UI(ID_VIEW_QUAD, OnUpdateViewQuad)
	ON_COMMAND(ID_VIEW_FILL, OnViewFill)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FILL, OnUpdateViewFill)
	//ON_COMMAND(ID_EDIT_PROP, OnEditProp)
	ON_COMMAND(ID_EDIT_BACKGROUND, OnEditBackground)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLView message handlers

COpenGLView::~COpenGLView() {}

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	return CView::PreCreateWindow(cs);
}

BOOL COpenGLView::OnEraseBkgnd(CDC* pDC) { return TRUE; }

COpenGLView::COpenGLView()
{
	//No Context ATM
	cont = 0;

	//Default Angles
	theta_x = 35.f;
	theta_y = 20.f;

	//View Angle
	theta_per = 45.f;

	//Inittial Background Color
	backCol = RGB(0, 0, 96);

	//Initially fill quads
	fillmode = GL_FILL;

	//Set R3
	DefaultGraphic();

	//Initial shifts
	shift_z = -1.5f*range_x;
	shift_x = shift_y = 0.f;

	//Set infinitesimals
	dx = dy = 0.f;

	clicked = false;
	right = false;
	quad = false;

	//Set lighting
	m_Lighting[0] = 50;   // X position
	m_Lighting[1] = 80;   // Y position
	m_Lighting[2] = 100;  // Z position
	m_Lighting[3] = 15;   // Ambient light
	m_Lighting[4] = 70;   // Diffuse light
	m_Lighting[5] = 100;  // Specular light
	m_Lighting[6] = 100;  // Ambient material
	m_Lighting[7] = 100;  // Diffuse material
	m_Lighting[8] = 40;   // Specular material
	m_Lighting[9] = 70;   // Shininess material
	m_Lighting[10] = 0;   // Emission material
}

int COpenGLView::OnCreate(LPCREATESTRUCT createStruct)
{
	if (CView::OnCreate(createStruct) == -1) return -1;

	// Format description
	PIXELFORMATDESCRIPTOR pixelDesc =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1, //Version #
		PFD_DRAW_TO_WINDOW | // GDI support
		PFD_SUPPORT_OPENGL | // OpenGL support
		PFD_DOUBLEBUFFER, //Double buffer
		PFD_TYPE_RGBA, //Do not use pallettes
		24, //# of color planes per buffer
		24, 0, //Red
		24, 0, //Blue
		24, 0, //Green
		24, 0, //Alpha
		0, //# of planes of acc buffer
		0, //Red
		0, //Green
		0, //Blue
		0, //Alpha
		32, //Depth z
		0, //Depth stencil
		0, //Depth aux
		0, //Ignored
		0, //# of planes
		0, //Ignored
		0, //Mask col
		0  //Ignored
	};

	//Get Windows Context
	dcont = ::GetDC(GetSafeHwnd());

	//Find pixelFormat
	int a = ChoosePixelFormat(dcont, &pixelDesc);
	if (!a) return -1;

	//Set pixel format
	if (!SetPixelFormat(dcont, a, &pixelDesc)) return -1;

	//Create OpenGL context
	if (!(cont = wglCreateContext(dcont))) return -1;

	//Initialize context
	if (!wglMakeCurrent(dcont, cont)) return -1;

	//OpenGL
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	SetBackgroundColor();

	DrawScene();
	return 0;
}

void COpenGLView::OnDraw(CDC* DC)
{
	//Clear Background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Clean models
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	SetLight();

	//Mutate coefficients
	glTranslatef(shift_x, shift_y, shift_z);
	glRotatef(theta_x, 1.0f, 0.0f, 0.0f);
	glRotatef(theta_y, 0.0f, 1.0f, 0.0f);

	glCallList(1);

	SwapBuffers(dcont);
}

void COpenGLView::SetLight()
{
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

	float positions[] =
	{
		(m_Lighting[0] - 50)*range_x / 100,
		(m_Lighting[1] - 50)*range_y / 100,
		(m_Lighting[2] - 50)*range_z / 100,
		1.f
	};

	glLightfv(GL_LIGHT0, GL_POSITION, positions);

	//Intensities
	//Ambient
	float f = m_Lighting[3] / 100.f;
	float fAmbient[4] = { f,f,f,0.f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, fAmbient);
	//Diffuse
	f = m_Lighting[4] / 100.f;
	float fDiffuse[4] = { f,f,f,0.f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, fDiffuse);
	//Specular
	f = m_Lighting[5] / 100.f;
	float fSpecular[4] = { f, f, f, 0.f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, fSpecular);
	
	
	//Reflection
	f = m_Lighting[6] / 100.f;
	float fAmbMat[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fAmbMat);

	f = m_Lighting[7] / 100.f;
	float fDifMat[4] = { f, f, f, 1.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fDifMat);

	f = m_Lighting[8] / 100.f;
	float fSpecMat[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, fSpecMat);

	//Shine
	float fShine = 128 * m_Lighting[9] / 100.f;
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, fShine);

	//Emission
	f = m_Lighting[10] / 100.f;
	float fEmission[4] = { f, f, f, 0.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, fEmission);
}

void COpenGLView::SetBackgroundColor()
{
	//Color components
	GLclampf
		r = GetRValue(backCol) / 255.f,
		g = GetGValue(backCol) / 255.f,
		b = GetBValue(backCol) / 255.f;

	//Clear background
	glClearColor(r, g, b, 0.f);

	//Erase background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void COpenGLView::DrawScene()
{
	//Initialize list of commands
	glNewList(1, GL_COMPILE);

	//Polygon fill mode
	glPolygonMode(GL_FRONT_AND_BACK, fillmode);

	//Sizing
	UINT nx = x_size - 1,
		nz = z_size - 1;

	//Connection mode
	if (quad)
		glBegin(GL_QUADS);

	for (UINT z = 0, i = 0; z < nz; z++, i++)
	{
		if (!quad)
			glBegin(GL_QUAD_STRIP);

		for (UINT x = 0; x < nx; x++, i++)
		{
			// i, j, k, n  4 indices of a quad
			// Counter Clockwise direction

			int   j = i + x_size, // Other vertices indices
				k = j + 1,
				n = i + 1;

			//=== Get coordinates of 4 vertices
			float
				xi = points[i].x,
				yi = points[i].y,
				zi = points[i].z,

				xj = points[j].x,
				yj = points[j].y,
				zj = points[j].z,

				xk = points[k].x,
				yk = points[k].y,
				zk = points[k].z,

				xn = points[n].x,
				yn = points[n].y,
				zn = points[n].z,

				//=== Quad side lines vectors coordinates
				ax = xi - xn,
				ay = yi - yn,

				by = yj - yi,
				bz = zj - zi,

				//====== Normal vector coordinates
				vx = ay*bz,
				vy = -bz*ax,
				vz = ax*by,

				//====== Normal vector length
				v = float(sqrt(vx*vx + vy*vy + vz*vz));

			//====== Scale to unity
			vx /= v;
			vy /= v;
			vz /= v;

			//====== Set the normal vector
			glNormal3f(vx, vy, vz);

			//===== Not connected quads branch
			if (quad)
			{
				//====== Vertices are given in counter clockwise 
				//       direction order
				glColor3f(0.2f, 0.8f, 1.f);
				glVertex3f(xi, yi, zi);
				glColor3f(0.6f, 0.7f, 1.f);
				glVertex3f(xj, yj, zj);
				glColor3f(0.7f, 0.9f, 1.f);
				glVertex3f(xk, yk, zk);
				glColor3f(0.7f, 0.8f, 1.f);
				glVertex3f(xn, yn, zn);
			}
			else
				//===== Connected quads branch
			{
				glColor3f(0.9f, 0.9f, 1.0f);
				glVertex3f(xi, yi, zi);
				glColor3f(0.5f, 0.8f, 1.0f);
				glVertex3f(xj, yj, zj);
			}
		}
	}

	if (quad) glEnd();
	glEndList();
}

void COpenGLView::DefaultGraphic()
{
	//====== Coordinate grid dimensions
	x_size = z_size = 33;

	//====== Number of meshes is less than number of nodes
	UINT   nz = z_size - 1,
		nx = x_size - 1;

	// File size in bytes
	DWORD nSize =
		x_size * z_size * sizeof(float) + 2 * sizeof(UINT);

	//====== Temporary buffer
	BYTE *buff = new BYTE[nSize + 1];

	//====== Point at the start of it with UINT-type pointer
	UINT *p = (UINT*)buff;

	//====== Place the two UINTs
	*p++ = x_size;
	*p++ = z_size;

	//====== Change the pointer type to continue with the 
	//       floating numbers
	float *pf = (float*)p;

	//=== Default formula coefficients
	double   fi = atan(1.) * 6,
		kx = fi / nx,
		kz = fi / nz;

	//====== For all the grid nodes calculate
	//=== calculate and place default function values 
	//                in the same buffer
	for (UINT i = 0; i < z_size; i++)
	{
		for (UINT j = 0; j < x_size; j++)
		{
			//====== Sample function
			*pf++ =
				float(sin(kz*(i - nz / 2.)) * sin(kx*(j - nx / 2.)));
		}
	}

	//=== We want to know the real number of bytes written
	//    to the file
	DWORD nBytes;

	//=== Create and open the default data file (sin.dat)
	HANDLE hFile = CreateFile(_T("sin.dat"),
		GENERIC_WRITE,
		0, 0,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		0);

	//====== Write the whole buffer
	WriteFile(hFile, (LPCVOID)buff, nSize, &nBytes, 0);

	//====== Close the file
	CloseHandle(hFile);

	//====== Create and fill container m_cPoints 
	//                  (using the same buffer)
	SetGraphPoints(buff, nSize);

	//====== Free temporary buffer
	delete[] buff;
}

void COpenGLView::ReadData()
{
	//=== Here we place the file path 
	TCHAR szFile[MAX_PATH] = { 0 };

	//====== File extensions filter
	TCHAR *szFilter = TEXT("Graphics Data Files (*.dat)\0")
		TEXT("*.dat\0")
		TEXT("All Files\0")
		TEXT("*.*\0");

	//====== Query the current folder
	TCHAR szCurDir[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH - 1, szCurDir);

	//=== Struct used by the standard file dialog
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	//====== Dialog parameters
	ofn.lStructSize = sizeof(OPENFILENAME);
	//====== Window which owns the dialog
	ofn.hwndOwner = GetSafeHwnd();
	ofn.lpstrFilter = szFilter;
	//====== The filters string index (begins with 1)
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	//====== Dialog caption
	ofn.lpstrTitle = _T("Find a data file");
	ofn.nMaxFileTitle = sizeof(ofn.lpstrTitle);
	//====== Dialog style (only in Win2K)
	ofn.Flags = OFN_EXPLORER;

	//====== Create and open the dialog (retuns 0 on failure)
	if (GetOpenFileName(&ofn))
	{
		// Try to open the file (which must exist)
		HANDLE hFile = CreateFile(ofn.lpstrFile, GENERIC_READ,
			FILE_SHARE_READ, 0, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, 0);

		//=== On failure CreateFile returns -1
		if (hFile == (HANDLE)-1)
		{
			MessageBox(_T("Could not open this file"));
			return;
		}

		//====== Try to read the data
		if (!Read(hFile))
			return;

		//====== Create and store the image
		DrawScene();

		//====== Redraw the window client region
		Invalidate(FALSE);
	}
}

bool COpenGLView::Read(HANDLE hFile)
{
	//===== Query the file size
	DWORD nSize = GetFileSize(hFile, 0);

	if (nSize == 0xFFFFFFFF)
	{
		GetLastError();
		MessageBox(_T("Could not get file size"));
		CloseHandle(hFile);
		return false;
	}

	//===== Try to allocate the core
	BYTE *buff = new BYTE[nSize + 1];

	if (!buff)
	{
		MessageBox(_T("The data file is too big"));
		CloseHandle(hFile);
		return false;
	}

	DWORD nBytes;
	//===== Read the whole file in the buffer
	ReadFile(hFile, buff, nSize, &nBytes, 0);
	CloseHandle(hFile);

	if (nSize != nBytes)
	{
		MessageBox(_T("Error while reading data file"));
		return false;
	}

	//===== Set the vector of vertices coordinates
	SetGraphPoints(buff, nSize);

	delete[] buff;
	return true;
}

void MinMax(float d, float& Min, float& Max)
{
	if (d > Max)
		Max = d;
	else if (d < Min)
		Min = d;
}

void COpenGLView::SetGraphPoints(BYTE* buff, DWORD nSize)
{
	//===== Here again we use the technique of changing 
	//       the the pointer types
	UINT *p = (UINT*)buff;

	//==== First read the grid dimensions
	x_size = *p;
	z_size = *++p;

	//===== Check the file size (just in case)
	if (x_size<2 || z_size < 2 ||
		x_size*z_size * sizeof(float) + 2 * sizeof(UINT) != nSize)
	{
		MessageBox(_T("Wrong data format"));
		return;
	}

	//===== Resize the container
	points.resize(x_size*z_size);

	if (points.empty())
	{
		MessageBox(_T("Can not allocate the data"));
		return;
	}

	//====== Change the pointer type
	float   x, z,
		*pf = (float*)++p,
		fMinY = *pf,
		fMaxY = *pf,
		right = (x_size - 1) / 2.f,
		left = -right,
		rear = (z_size - 1) / 2.f,
		front = -rear,
		range = (right + rear) / 2.f;

	UINT   i, j, n;

	range_y = range;
	range_x = float(x_size);
	range_z = float(z_size);

	//===== How far should we place the whole image
	shift_z = -1.5f * range_z;

	//===== Fill the container with 3D poits
	for (z = front, i = 0, n = 0; i < z_size; i++, z += 1.f)
	{
		for (x = left, j = 0; j < x_size; j++, x += 1.f, n++)
		{
		    MinMax(*pf, fMinY, fMaxY);
			points[n] = CPointR3(x, z, *pf++);
		}
	}

	//===== Scale the data so that any data would be seen "nicely"
	float zoom = fMaxY > fMinY ? range / (fMaxY - fMinY) : 1.f;

	for (n = 0; n < x_size*z_size; n++)
	{
		points[n].y = zoom * (points[n].y - fMinY) - range / 2.f;
	}
}


void COpenGLView::RestrictAngles()
{
	while (theta_x < -360.f)
		theta_x += 360.f;
	while (theta_x > 360.f)
		theta_x -= 360.f;
	while (theta_y < -360.f)
		theta_y += 360.f;
	while (theta_y > 360.f)
		theta_y -= 360.f;
}

void COpenGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//====== Stop rotation
	KillTimer(1);

	//====== Zero the quantums
	dx = 0.f;
	dy = 0.f;

	//====== Capture the mouse messages and direct them 
	//       in our window
	SetCapture();
	//====== Remember the fact
	clicked = true;
	//====== and where it happened
	mouse_pos = point;
}

void COpenGLView::OnRButtonDown(UINT nFlags, CPoint point)
{
	//====== Remember the fact
	right = true;

	//====== and reproduce the left button response
	OnLButtonDown(nFlags, point);
}

void COpenGLView::OnLButtonUp(UINT nFlags, CPoint point)
{
	//====== If we captured the mouse,
	if (clicked)
	{
		//=== query the desired quantum value
		//=== if it exeeds the sensativity threshold
		if (fabs(dx) > 0.5f || fabs(dy) > 0.5f)
			//=== Turn on the constant rotation
			SetTimer(1, 33, 0);
		else
			//=== Turn off the constant rotation
			KillTimer(1);

		//====== Clear the capture flag
		clicked = false;
		ReleaseCapture();
	}
}


void COpenGLView::OnRButtonUp(UINT nFlags, CPoint point)
{
    right = clicked = false;
	ReleaseCapture();
}

void COpenGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (clicked)
	{
		// Desired rotation speed components
		dy = float(point.y - mouse_pos.y) / 40.f;
		dx = float(point.x - mouse_pos.x) / 40.f;

		//====== If Ctrl was pressed
		if (nFlags & MK_CONTROL)
		{
			//=== we shift (translate) the image
			shift_x += dx;
			shift_y -= dy;
		}
		else
		{
			//====== If the right mouse button is pressed
			if (right)
				//====== we shift along the z-axis
				shift_z += (dx + dy) / 2.f;
			else
			{
				//====== otherwise we rotate the image
				RestrictAngles();
				double a = fabs(theta_x);
				if (90. < a && a < 270.)
					dx = -dx;
				theta_x += dy;
				theta_y += dx;
			}
		}
		//=== In any case we should store the coordinates
		mouse_pos = point;
		Invalidate(FALSE);
	}
}

void COpenGLView::OnTimer(UINT nIDEvent)
{
	RestrictAngles();
	//====== Increase the angles
	theta_x += dy;
	theta_y += dx;
	Invalidate(FALSE);
}

void COpenGLView::GetAllLighting(int *pPos)
{
	for (int i = 0; i<11; i++)
		pPos[i] = m_Lighting[i];
}

void COpenGLView::OnViewQuad(void)
{
	quad = !quad;

	DrawScene();
	Invalidate(FALSE);
	UpdateWindow();
}


void COpenGLView::OnUpdateViewQuad(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(quad == true);
}

void COpenGLView::OnViewFill(void)
{
	fillmode = fillmode == GL_FILL ? GL_LINE : GL_FILL;

	DrawScene();
	Invalidate(FALSE);
	UpdateWindow();
}


void COpenGLView::OnUpdateViewFill(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(fillmode == GL_FILL);
}

void COpenGLView::OnEditBackground(void)
{
	CColorDialog dlg(backCol);
	dlg.m_cc.Flags |= CC_FULLOPEN;
	if (dlg.DoModal() == IDOK)
	{
		backCol = dlg.m_cc.rgbResult;
		SetBackgroundColor();
		Invalidate(FALSE);
	}
}

void COpenGLView::SetLighting(short lp, int nPos)
{
	m_Lighting[lp] = nPos;
	Invalidate(FALSE);
}