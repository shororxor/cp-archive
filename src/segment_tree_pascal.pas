// #pascal | #segment_tree

program SegmentTreeLazy;

uses
 	Math;

const
 	MAXN = 100005;
 	NEGINF = -1000000000;

type
 	TSegTree = object
    	n: Int64;
    	node, lazy: array[1..4 * MAXN] of Int64;

	    procedure Init(n_: Int64);
	    procedure PushDown(i: Int64);
	    procedure Update(i, L_, R_, u, v, c: Int64);
	    function Query(i, L_, R_, u, v: Int64): Int64;
  	end;

procedure TSegTree.Init(n_: Int64);
var
 	i: Int64;
begin
  	n := n_;
  	for i := 1 to 4 * n do
  	begin
    	node[i] := 0;
    	lazy[i] := 0;
  	end;
end;

procedure TSegTree.PushDown(i: Int64);
begin
  	if lazy[i] = 0 then Exit;
  	node[i * 2] := node[i * 2] + lazy[i];
  	node[i * 2 + 1] := node[i * 2 + 1] + lazy[i];
  	lazy[i * 2] := lazy[i * 2] + lazy[i];
  	lazy[i * 2 + 1] := lazy[i * 2 + 1] + lazy[i];
  	lazy[i] := 0;
end;

procedure TSegTree.Update(i, L_, R_, u, v, c: Int64);
var
  	m: Int64;
begin
  	if (R_ < u) or (L_ > v) or (L_ > R_) or (u > v) then Exit;
  	if (u <= L_) and (R_ <= v) then
  	begin
    	node[i] := node[i] + c;
    	lazy[i] := lazy[i] + c;
    	Exit;
  	end;

  	PushDown(i);
  	m := (L_ + R_) div 2;
  	Update(i * 2, L_, m, u, v, c);
  	Update(i * 2 + 1, m + 1, R_, u, v, c);
  	node[i] := Max(node[i * 2], node[i * 2 + 1]);
end;

function TSegTree.Query(i, L_, R_, u, v: Int64): Int64;
var
 	m, Lres, Rres: Int64;
begin
 	if (R_ < u) or (L_ > v) or (L_ > R_) or (u > v) then
  	begin
    	Query := NEGINF;
    	Exit;
  	end;

  	if (u <= L_) and (R_ <= v) then
  	begin
    	Query := node[i];
    	Exit;
  	end;

  	PushDown(i);
  	m := (L_ + R_) div 2;
  	Lres := Query(i * 2, L_, m, u, v);
  	Rres := Query(i * 2 + 1, m + 1, R_, u, v);
  	Query := Max(Lres, Rres);
end;


var
 	tree: TSegTree;
  	n, i, q, t, l1, r1, x, c: Int64;

begin
 	ReadLn(n);
  	tree.Init(n);
  	for i := 1 to n do
  	begin
    	Read(x);
    	tree.Update(1, 1, n, i, i, x);
  	end;

  	ReadLn(q);
  	for i := 1 to q do
  	begin
    	Read(t, l1, r1);
    	if t = 1 then
    	begin
      		Read(c);
      		tree.Update(1, 1, n, l1, r1, c);
    	end
    	else
    	begin
     		WriteLn(tree.Query(1, 1, n, l1, r1));
    	end;
  	end;
end.
