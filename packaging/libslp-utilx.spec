Name:	    libslp-utilx
Summary:    utilX 
Version:	0.1.7
Release:    1.1
Group:      System/Libraries
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001: packaging/libslp-utilx.manifest 
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

BuildRequires: cmake
BuildRequires: pkgconfig(x11)

%description
Utility functions for the XWindow


%package devel
Summary:    utilX
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}

%description devel
Utility functions for the XWindow (developement files)

%prep
%setup -q


%build
cp %{SOURCE1001} .
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix}


make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest libslp-utilx.manifest
%defattr(-,root,root,-)
/usr/lib/libutilX.so.*


%files devel
%manifest libslp-utilx.manifest
%defattr(-,root,root,-)
/usr/include/utilX.h
/usr/lib/libutilX.so
/usr/lib/pkgconfig/utilX.pc




