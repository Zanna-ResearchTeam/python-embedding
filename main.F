

      SubRoutine PrintX(X, Nx)
      Implicit None
      Integer Nx
      Real*8 X(*)
      Integer I

      Do I = 1, Nx
         Write(6, *) I, X(I)
      EndDo

      Call Flush(6)

      Return
      End
      

      Program Main
      Implicit None
      Integer Nx
      Integer NY
      Parameter(Nx = 1250)
      Parameter(Ny = 100)
      Real*8 X(Nx)
      Real*8 Y(Ny)
      Integer I

      Do I = 1, Nx
         X(I) = DBLE(I) / DBLE(100)
      EndDo

      Do I = 1, Ny
         Y(I) = DBLE(0.)
      EndDo
      
      Call PrintX(X, 10)
      Call PrintX(Y, 10)

      Do I = 1, 10
         Write(6, *)
         Write(6, *) 'Loop: ', I
         Call RunPy('testNN.py', 'my_testNN', X, Nx, Y, Ny)
         Call PrintX(Y, 10)
      EndDo

      Call PyFinalize
      
      End


